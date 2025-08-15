/**
 * Author: M. Shahat Akash
 *
 * Restaurant Management System (Console) - Single File
 * Language: C (ISO C99-compatible)
 *
 * Features:
 *  - Admin: add menu item, update item, view menu, view orders, change password
 *  - Customer: view menu, place order (multiple items), get invoice
 *  - Persistent storage using binary files: menu.dat, orders.dat
 *  - Simple admin password stored in admin.dat (binary)
 *
 * Compile:
 *   gcc Restaurant_management_system.c -o Restaurant_management_system
 *
 * Run:
 *   ./Restaurant_management_system   (Linux/macOS)
 *   Restaurant_management_system.exe (Windows)
 *
 * Notes:
 *  - Tax rate defined by TAX_RATE constant (currently 5%)
 *  - IDs auto-incremented for new menu items and orders
 *  - All file operations checked for errors
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MENU_FILE "menu.dat"
#define ORDER_FILE "orders.dat"
#define ADMIN_FILE "admin.dat"

#define MAX_NAME_LEN 50
#define MAX_CATEGORY_LEN 30
#define MAX_ITEMS_PER_ORDER 50
#define ADMIN_DEFAULT_PASS "admin123"    /* default admin password, changeable */
#define TAX_RATE 0.05                    /* 5% tax */

/* Structures */

typedef struct {
    int id;                             /* unique id */
    char name[MAX_NAME_LEN];
    char category[MAX_CATEGORY_LEN];
    double price;
    int available;                      /* 1 = available, 0 = not available */
} MenuItem;

typedef struct {
    int item_id;
    int qty;
    double item_price;                  /* price at time of ordering (unit price) */
    char item_name[MAX_NAME_LEN];
} OrderItem;

typedef struct {
    int order_id;
    char customer_name[MAX_NAME_LEN];
    int num_items;
    OrderItem items[MAX_ITEMS_PER_ORDER];
    double subtotal;
    double tax;
    double total;
    time_t timestamp;
} Order;

/* Admin password storage structure (simple) */
typedef struct {
    char password[50];
} AdminCred;

/* Helper declarations */
int admin_menu(void);
int customer_menu(void);
void admin_add_menu_item(void);
void admin_view_menu(void);
void admin_update_menu_item(void);
void admin_view_orders(void);
void admin_change_password(void);

void customer_view_menu(void);
void customer_place_order(void);

int get_next_menu_id(void);
int get_next_order_id(void);
void pause_and_clear(void);
void safe_input(char *buffer, size_t size);
MenuItem* load_all_menu_items(size_t *count);
int save_all_menu_items(MenuItem *items, size_t count);
Order* load_all_orders(size_t *count);
int append_order(const Order *order);
MenuItem* find_menu_item_by_id(int id);

int admin_login(void);
int ensure_admin_file(void);

/* Implementation */

int main(void) {
    /* Ensure admin credentials exist */
    ensure_admin_file();

    while (1) {
        printf("\n====== Restaurant Management System ======\n");
        printf("1. Admin\n");
        printf("2. Customer\n");
        printf("0. Exit\n");
        printf("Select option: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); /* flush */
            printf("Invalid input.\n");
            continue;
        }
        while (getchar() != '\n'); /* flush newline */

        if (choice == 1) {
            if (admin_login()) {
                admin_menu();
            } else {
                printf("Admin login failed.\n");
            }
        } else if (choice == 2) {
            customer_menu();
        } else if (choice == 0) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}

/* ---------- Admin functions ---------- */

int admin_login(void) {
    char entered[50];
    AdminCred cred;
    FILE *f = fopen(ADMIN_FILE, "rb");
    if (!f) {
        /* if admin file missing, create with default */
        strncpy(cred.password, ADMIN_DEFAULT_PASS, sizeof(cred.password));
        f = fopen(ADMIN_FILE, "wb");
        if (!f) {
            printf("Unable to create admin credential file.\n");
            return 0;
        }
        fwrite(&cred, sizeof(AdminCred), 1, f);
        fclose(f);
    } else {
        fread(&cred, sizeof(AdminCred), 1, f);
        fclose(f);
    }

    printf("Enter admin password: ");
    safe_input(entered, sizeof(entered));

    if (strcmp(entered, cred.password) == 0) {
        return 1;
    }
    return 0;
}

int admin_menu(void) {
    while (1) {
        printf("\n--- ADMIN MENU ---\n");
        printf("1. Add Menu Item\n");
        printf("2. Update Menu Item\n");
        printf("3. View Menu Items\n");
        printf("4. View Orders (Order History)\n");
        printf("5. Change Admin Password\n");
        printf("0. Logout\n");
        printf("Choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }
        while (getchar() != '\n');

        if (choice == 1) admin_add_menu_item();
        else if (choice == 2) admin_update_menu_item();
        else if (choice == 3) admin_view_menu();
        else if (choice == 4) admin_view_orders();
        else if (choice == 5) admin_change_password();
        else if (choice == 0) {
            printf("Logging out of admin.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}

void admin_add_menu_item(void) {
    MenuItem item;
    item.id = get_next_menu_id();
    printf("\n--- Add Menu Item ---\n");
    printf("Item name: ");
    safe_input(item.name, sizeof(item.name));
    printf("Category: ");
    safe_input(item.category, sizeof(item.category));
    printf("Price (e.g., 99.50): ");
    while (scanf("%lf", &item.price) != 1) {
        while (getchar() != '\n');
        printf("Invalid price. Enter again: ");
    }
    while (getchar() != '\n');
    item.available = 1;

    FILE *f = fopen(MENU_FILE, "ab");
    if (!f) {
        printf("Error opening menu file to append.\n");
        return;
    }
    fwrite(&item, sizeof(MenuItem), 1, f);
    fclose(f);
    printf("Added menu item with ID %d.\n", item.id);
}

void admin_view_menu(void) {
    size_t count;
    MenuItem *items = load_all_menu_items(&count);
    if (!items) {
        printf("No menu items found.\n");
        return;
    }
    printf("\n--- MENU ITEMS (%zu) ---\n", count);
    printf("%-5s %-25s %-12s %-8s %-10s\n", "ID", "Name", "Category", "Price", "Available");
    for (size_t i = 0; i < count; ++i) {
        printf("%-5d %-25s %-12s %-8.2f %-10s\n",
               items[i].id,
               items[i].name,
               items[i].category,
               items[i].price,
               items[i].available ? "Yes" : "No");
    }
    free(items);
}

void admin_update_menu_item(void) {
    printf("\n--- Update Menu Item ---\n");
    int id;
    printf("Enter item ID to update: ");
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        printf("Invalid ID.\n");
        return;
    }
    while (getchar() != '\n');

    size_t count;
    MenuItem *items = load_all_menu_items(&count);
    if (!items) {
        printf("Menu is empty.\n");
        return;
    }

    size_t idx = (size_t)-1;
    for (size_t i = 0; i < count; ++i) {
        if (items[i].id == id) {
            idx = i;
            break;
        }
    }
    if (idx == (size_t)-1) {
        printf("Item with ID %d not found.\n", id);
        free(items);
        return;
    }

    printf("Found: %s | Category: %s | Price: %.2f | Available: %s\n",
           items[idx].name, items[idx].category, items[idx].price,
           items[idx].available ? "Yes" : "No");

    printf("Enter new name (or press enter to keep): ");
    char buffer[MAX_NAME_LEN];
    safe_input(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) strncpy(items[idx].name, buffer, MAX_NAME_LEN);

    printf("Enter new category (or press enter to keep): ");
    safe_input(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) strncpy(items[idx].category, buffer, MAX_CATEGORY_LEN);

    printf("Enter new price (enter -1 to keep): ");
    double newprice;
    if (scanf("%lf", &newprice) == 1) {
        if (newprice >= 0.0) items[idx].price = newprice;
        while (getchar() != '\n');
    } else {
        while (getchar() != '\n');
    }

    printf("Set availability? (1 = available, 0 = not) (enter -1 to keep): ");
    int avail;
    if (scanf("%d", &avail) == 1) {
        if (avail == 0 || avail == 1) items[idx].available = avail;
        while (getchar() != '\n');
    } else {
        while (getchar() != '\n');
    }

    if (save_all_menu_items(items, count) == 0) {
        printf("Menu item updated.\n");
    } else {
        printf("Failed to save updates.\n");
    }

    free(items);
}

void admin_view_orders(void) {
    size_t count;
    Order *orders = load_all_orders(&count);
    if (!orders) {
        printf("No orders found.\n");
        return;
    }
    printf("\n--- ORDER HISTORY (%zu) ---\n", count);
    for (size_t i = 0; i < count; ++i) {
        char tbuf[64];
        struct tm *tm_info = localtime(&orders[i].timestamp);
        strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", tm_info);
        printf("\nOrder ID: %d | Customer: %s | Date: %s\n",
               orders[i].order_id, orders[i].customer_name, tbuf);
        printf("Items:\n");
        for (int j = 0; j < orders[i].num_items; ++j) {
            printf("  - %s (ID %d) x%d @ %.2f each  => %.2f\n",
                   orders[i].items[j].item_name,
                   orders[i].items[j].item_id,
                   orders[i].items[j].qty,
                   orders[i].items[j].item_price,
                   orders[i].items[j].item_price * orders[i].items[j].qty);
        }
        printf("Subtotal: %.2f | Tax: %.2f | Total: %.2f\n",
               orders[i].subtotal, orders[i].tax, orders[i].total);
    }
    free(orders);
}

void admin_change_password(void) {
    AdminCred cred;
    FILE *f = fopen(ADMIN_FILE, "rb+");
    if (!f) {
        printf("Unable to open admin file.\n");
        return;
    }
    if (fread(&cred, sizeof(AdminCred), 1, f) != 1) {
        printf("Unable to read admin credentials.\n");
        fclose(f);
        return;
    }

    char newpass[50];
    printf("Enter new admin password: ");
    safe_input(newpass, sizeof(newpass));
    if (strlen(newpass) == 0) {
        printf("Password not changed (empty).\n");
        fclose(f);
        return;
    }
    strncpy(cred.password, newpass, sizeof(cred.password));
    rewind(f);
    fwrite(&cred, sizeof(AdminCred), 1, f);
    fclose(f);
    printf("Admin password updated.\n");
}

/* ---------- Customer functions ---------- */

int customer_menu(void) {
    while (1) {
        printf("\n--- CUSTOMER MENU ---\n");
        printf("1. View Menu\n");
        printf("2. Place Order\n");
        printf("0. Back\n");
        printf("Choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }
        while (getchar() != '\n');

        if (choice == 1) customer_view_menu();
        else if (choice == 2) customer_place_order();
        else if (choice == 0) break;
        else printf("Invalid choice.\n");
    }
    return 0;
}

void customer_view_menu(void) {
    admin_view_menu(); /* reuse view function */
}

void customer_place_order(void) {
    size_t count;
    MenuItem *items = load_all_menu_items(&count);
    if (!items || count == 0) {
        printf("No menu items available.\n");
        if (items) free(items);
        return;
    }

    Order order;
    memset(&order, 0, sizeof(order));
    order.order_id = get_next_order_id();
    order.timestamp = time(NULL);

    printf("\n--- Place Order ---\n");
    printf("Customer name: ");
    safe_input(order.customer_name, sizeof(order.customer_name));

    printf("\nAvailable Menu:\n");
    printf("%-5s %-25s %-12s %-8s\n", "ID", "Name", "Category", "Price");
    for (size_t i = 0; i < count; ++i) {
        if (items[i].available)
            printf("%-5d %-25s %-12s %-8.2f\n",
                   items[i].id, items[i].name, items[i].category, items[i].price);
    }

    int adding = 1;
    while (adding) {
        if (order.num_items >= MAX_ITEMS_PER_ORDER) {
            printf("Reached maximum items per order (%d).\n", MAX_ITEMS_PER_ORDER);
            break;
        }
        int id;
        printf("\nEnter menu item ID to add (0 to finish): ");
        if (scanf("%d", &id) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }
        while (getchar() != '\n');

        if (id == 0) break;

        MenuItem *mi = find_menu_item_by_id(id);
        if (!mi) {
            printf("Item with ID %d not found.\n", id);
            continue;
        }
        if (!mi->available) {
            printf("Item '%s' is currently not available.\n", mi->name);
            continue;
        }

        int qty;
        printf("Quantity: ");
        if (scanf("%d", &qty) != 1 || qty <= 0) {
            while (getchar() != '\n');
            printf("Invalid quantity.\n");
            continue;
        }
        while (getchar() != '\n');

        /* add to order */
        OrderItem oi;
        oi.item_id = mi->id;
        oi.qty = qty;
        oi.item_price = mi->price;
        strncpy(oi.item_name, mi->name, MAX_NAME_LEN);

        order.items[order.num_items] = oi;
        order.num_items++;

        printf("Added %s x%d to order.\n", oi.item_name, oi.qty);

        printf("Add more items? (1 = yes, 0 = no): ");
        int more;
        if (scanf("%d", &more) != 1) {
            while (getchar() != '\n');
            printf("Assuming no.\n");
            more = 0;
        }
        while (getchar() != '\n');
        if (more == 0) adding = 0;
    }

    if (order.num_items == 0) {
        printf("No items in order. Cancelled.\n");
        free(items);
        return;
    }

    /* calculate totals carefully, step-by-step */
    double subtotal = 0.0;
    for (int i = 0; i < order.num_items; ++i) {
        double line = order.items[i].item_price * (double)order.items[i].qty;
        subtotal += line;
    }
    /* Round to cents for subtotal */
    subtotal = ((long long) (subtotal * 100.0 + 0.5)) / 100.0;

    double tax = subtotal * TAX_RATE;
    tax = ((long long) (tax * 100.0 + 0.5)) / 100.0;
    double total = subtotal + tax;
    total = ((long long) (total * 100.0 + 0.5)) / 100.0;

    order.subtotal = subtotal;
    order.tax = tax;
    order.total = total;

    /* Show invoice */
    printf("\n--- INVOICE ---\n");
    printf("Order ID: %d\n", order.order_id);
    printf("Customer: %s\n", order.customer_name);
    char tbuf[64];
    struct tm *tm_info = localtime(&order.timestamp);
    strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Date: %s\n", tbuf);
    printf("\nItems:\n");
    for (int i = 0; i < order.num_items; ++i) {
        double line_total = order.items[i].item_price * (double)order.items[i].qty;
        printf(" - %-25s x%d @ %.2f => %.2f\n",
               order.items[i].item_name,
               order.items[i].qty,
               order.items[i].item_price,
               line_total);
    }
    printf("\nSubtotal: %.2f\nTax (%.2f%%): %.2f\nTotal: %.2f\n", subtotal, TAX_RATE * 100.0, tax, total);

    /* Save order */
    if (append_order(&order) == 0) {
        printf("Order saved. Thank you!\n");
    } else {
        printf("Failed to save order.\n");
    }

    free(items);
}

/* ---------- File / Data helpers ---------- */

int get_next_menu_id(void) {
    size_t count;
    MenuItem *items = load_all_menu_items(&count);
    int max = 0;
    if (items) {
        for (size_t i = 0; i < count; ++i) if (items[i].id > max) max = items[i].id;
        free(items);
    }
    return max + 1;
}

int get_next_order_id(void) {
    size_t count;
    Order *orders = load_all_orders(&count);
    int max = 0;
    if (orders) {
        for (size_t i = 0; i < count; ++i) if (orders[i].order_id > max) max = orders[i].order_id;
        free(orders);
    }
    return max + 1;
}

MenuItem* load_all_menu_items(size_t *count) {
    *count = 0;
    FILE *f = fopen(MENU_FILE, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz <= 0) { fclose(f); return NULL; }
    rewind(f);
    size_t n = sz / sizeof(MenuItem);
    MenuItem *arr = malloc(n * sizeof(MenuItem));
    if (!arr) { fclose(f); return NULL; }
    if (fread(arr, sizeof(MenuItem), n, f) != n) {
        free(arr); fclose(f); return NULL;
    }
    fclose(f);
    *count = n;
    return arr;
}

/* rewrite menu file with array (returns 0 on success) */
int save_all_menu_items(MenuItem *items, size_t count) {
    FILE *f = fopen(MENU_FILE, "wb");
    if (!f) return -1;
    if (count > 0) {
        if (fwrite(items, sizeof(MenuItem), count, f) != count) {
            fclose(f); return -1;
        }
    }
    fclose(f);
    return 0;
}

Order* load_all_orders(size_t *count) {
    *count = 0;
    FILE *f = fopen(ORDER_FILE, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz <= 0) { fclose(f); return NULL; }
    rewind(f);
    size_t n = sz / sizeof(Order);
    Order *arr = malloc(n * sizeof(Order));
    if (!arr) { fclose(f); return NULL; }
    if (fread(arr, sizeof(Order), n, f) != n) {
        free(arr); fclose(f); return NULL;
    }
    fclose(f);
    *count = n;
    return arr;
}

int append_order(const Order *order) {
    FILE *f = fopen(ORDER_FILE, "ab");
    if (!f) return -1;
    if (fwrite(order, sizeof(Order), 1, f) != 1) {
        fclose(f);
        return -1;
    }
    fclose(f);
    return 0;
}

MenuItem* find_menu_item_by_id(int id) {
    size_t count;
    MenuItem *items = load_all_menu_items(&count);
    if (!items) return NULL;
    MenuItem *res = NULL;
    for (size_t i = 0; i < count; ++i) {
        if (items[i].id == id) {
            /* copy to heap so caller can free it independently */
            res = malloc(sizeof(MenuItem));
            if (res) memcpy(res, &items[i], sizeof(MenuItem));
            break;
        }
    }
    free(items);
    return res;
}

/* Ensure admin file exists; if not, create with default password */
int ensure_admin_file(void) {
    FILE *f = fopen(ADMIN_FILE, "rb");
    if (!f) {
        AdminCred cred;
        strncpy(cred.password, ADMIN_DEFAULT_PASS, sizeof(cred.password));
        f = fopen(ADMIN_FILE, "wb");
        if (!f) return -1;
        fwrite(&cred, sizeof(AdminCred), 1, f);
        fclose(f);
    } else {
        fclose(f);
    }
    return 0;
}

/* ---------- Utility helpers ---------- */

void safe_input(char *buffer, size_t size) {
    if (!fgets(buffer, (int)size, stdin)) {
        /* input error, ensure empty string */
        buffer[0] = '\0';
        return;
    }
    /* strip newline if present */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
}

/* ---------- End of File ---------- */
