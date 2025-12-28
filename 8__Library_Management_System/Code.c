#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* BST node structure */
struct Book {
    int bookID;
    char title[50];
    struct Book *left;
    struct Book *right;
};

/* Create a new book node */
struct Book* createBook(int id, char title[]) {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    newBook->bookID = id;
    strcpy(newBook->title, title);
    newBook->left = NULL;
    newBook->right = NULL;
    return newBook;
}

/* Insert a book into BST */
struct Book* insertBook(struct Book* root, int id, char title[]) {
    if (root == NULL)
        return createBook(id, title);

    if (id < root->bookID)
        root->left = insertBook(root->left, id, title);
    else if (id > root->bookID)
        root->right = insertBook(root->right, id, title);
    else
        printf("Duplicate Book ID not allowed\n");

    return root;
}

/* Search a book */
struct Book* searchBook(struct Book* root, int id) {
    if (root == NULL || root->bookID == id)
        return root;

    if (id < root->bookID)
        return searchBook(root->left, id);
    else
        return searchBook(root->right, id);
}

/* Find minimum node (inorder successor) */
struct Book* findMin(struct Book* root) {
    if (root == NULL)
        return NULL;

    while (root->left != NULL)
        root = root->left;

    return root;
}

/* Delete a book */
struct Book* deleteBook(struct Book* root, int id) {
    if (root == NULL)
        return root;

    if (id < root->bookID) {
        root->left = deleteBook(root->left, id);
    }
    else if (id > root->bookID) {
        root->right = deleteBook(root->right, id);
    }
    else {
        /* Node found */
        if (root->left == NULL) {
            struct Book* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Book* temp = root->left;
            free(root);
            return temp;
        }

        /* Node with two children */
        struct Book* temp = findMin(root->right);
        root->bookID = temp->bookID;
        strcpy(root->title, temp->title);
        root->right = deleteBook(root->right, temp->bookID);
    }
    return root;
}

/* Inorder traversal */
void inorder(struct Book* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("Book ID: %d | Title: %s\n", root->bookID, root->title);
    inorder(root->right);
}

/* Main menu */
int main() {
    struct Book* root = NULL;
    int choice, id;
    char title[50];

    while (1) {
        printf("\n--- Library Book Management ---\n");
        printf("1. Insert Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. Display All Books\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter Book ID: ");
                scanf("%d", &id);
                printf("Enter Book Title: ");
                scanf(" %[^\n]", title);
                root = insertBook(root, id, title);
                break;

            case 2:
                if (root == NULL) {
                    printf("Library is Empty !!\n");
                } else {
                    printf("Enter Book ID to delete: ");
                    scanf("%d", &id);
                    root = deleteBook(root, id);
                }
                break;

            case 3: {
                if (root == NULL) {
                    printf("Library is Empty !!\n");
                } else {
                    struct Book* found;
                    printf("Enter Book ID to search: ");
                    scanf("%d", &id);
                    found = searchBook(root, id);

                    if (found)
                        printf("Book Found: %s\n", found->title);
                    else
                        printf("Book not found\n");
                }
                break;
            }

            case 4:
                if (root == NULL)
                    printf("Library is Empty !!\n");
                else {
                    printf("\nBooks in Library (Sorted by ID):\n");
                    inorder(root);
                }
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
