// Program for doing CRUD operations using linked list and to reduce disk I/O

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20
#define DATA_FILE "items.dat"
#define PRINT_NO_ITEMS printf("No items found. \n")
#define FILE_NOT_FOUND printf("File not found. \n")
#define PRINT_NOT_FOUND printf("Item not found. \n")
struct item
{
	char item_id[SIZE];
	char item_name[SIZE];
	float item_price;
	struct item *next;
};

void load_from_file();
void save_to_file();

void create_item();
void display_items();
void update_item(char *);
void delete_item(char *);

void append_node();

struct item *head = NULL;
struct item *new_node = NULL;
struct item *tail = NULL;

int main()
{
	int choice;
	load_from_file();
	char search_item_id[SIZE];
	while (1)
	{
		printf("1. Create item\n2. Display items\n3. Update item\n4. Delete item\n5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
		case 1:
			create_item();
			break;

		case 2:
			display_items();
			break;

		case 3:
			printf("Enter item id to update: ");
			scanf("%s", search_item_id);
			update_item(search_item_id);
			break;

		case 4:
			printf("Enter item id to delete: ");
			scanf("%s", search_item_id);
			delete_item(search_item_id);
			break;

		case 5:
			save_to_file();
			exit(0);

		default:
			printf("Invalid choice. \n");
		}

	}
}

void load_from_file()
{
    struct item item_record;

    FILE *fp_items = fopen(DATA_FILE, "rb");
    if (fp_items == NULL)
    {
    	FILE_NOT_FOUND;
        return;
    }

    while (fread(&item_record, sizeof(struct item) - sizeof(struct item *), 1, fp_items))
    {
        new_node = (struct item *)malloc(sizeof(struct item));
        *new_node = item_record;
        append_node();
    }
    fclose(fp_items);
}

void create_item()
{
	new_node = (struct item *)malloc(sizeof(struct item));

	printf("Enter Item Id: ");
	scanf("%s", new_node->item_id);
	printf("Enter Item Name: ");
	scanf("%s", new_node->item_name);
	printf("Enter Item price: ");
	scanf("%f", &new_node->item_price);
	append_node();
}

void display_items()
{
	struct item *current_node = head;
	if (current_node == NULL)
	{
		printf("No items found.\n");
		return;
	}
	while (current_node != NULL)
	{
		printf("Item Id: %s\nItem Name: %s\nItem Price: %.2f\n", current_node->item_id, current_node->item_name, current_node->item_price);
		current_node = current_node->next;
	}
}


void append_node()
{
	new_node->next = NULL;
	if (head == NULL)
	{
		head = new_node;
		tail = new_node;
	}
	else
	{
		tail->next = new_node;
		tail = new_node;
	}
}

void update_item(char search_item_id[SIZE])
{
	struct item *current_node = head;
    if (current_node == NULL)
    {
    	PRINT_NO_ITEMS;
    	return;
    }
     while (current_node != NULL)
     {
     	if (strcmp(current_node->item_id, search_item_id) == 0)
     	{
     		printf("Enter new item name: ");
     		scanf("%s", current_node->item_name);
     		printf("Enter new item price: ");
     		scanf("%f", &current_node->item_price);

     		printf("Item updated successfully.\n");
     		return;
     	}
     	current_node = current_node->next;
     }
     PRINT_NOT_FOUND;
}

void delete_item(char search_item_id[SIZE])
{
    struct item *current_node = head;
    struct item *previous_node = NULL;
    if (current_node == NULL)
    {
    	PRINT_NO_ITEMS;
    	return;
    }
    else
    {
    	while (current_node != NULL)
    	{
    		if (strcmp(current_node->item_id, search_item_id) == 0)
    		{
    			if (previous_node == NULL)
    			{
    				head = current_node->next;
    				if (head == NULL)
    				{
    					tail = NULL;
    				}
    			}
    			else
    			{
    				previous_node->next = current_node->next;
    				if (current_node == tail) 
    				{
    					tail = previous_node;
    				}
    			}
    			printf("Item deleted successfully.\n");
    			free(current_node);
    			return;
    		}
    		previous_node = current_node;
    		current_node = current_node->next;
    	}
    	PRINT_NOT_FOUND;
    }
}

void save_to_file()
{
    struct item *current_node = head;

    FILE *fp_items = fopen(DATA_FILE, "wb");
    if (fp_items == NULL)
    {
    	FILE_NOT_FOUND;
    	return;
    }

    while (current_node != NULL)
    {
    	fwrite(current_node, sizeof(struct item) - sizeof(struct item *), 1, fp_items);
    	current_node = current_node->next;
    }
    fclose(fp_items);
}
