#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// CONSTANTS

#define STR_SMALL 64
#define STR_MED   128
#define STR_LARGE 256

//  DATA STRUCTS

typedef struct {
    char content[STR_LARGE];
    char image_url[STR_MED];
    int likes_count;
    int comments_count;
    int user_id;
    char username[STR_SMALL];
    char user_avatar[STR_MED];
} SocialPost;

typedef struct {
    char product_id[STR_SMALL];
    char product_name[STR_SMALL];
    char category[STR_SMALL];
    double price;
    int stock;
    double rating;
} Product;

typedef struct {
    int user_id;
    char name[STR_SMALL];
    char email[STR_SMALL];
    char country[STR_SMALL];
    char signup_date[STR_SMALL];
    int is_active;
} UserProfile;

// UTILITY FUNCTIONS

int rand_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

double rand_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

void fake_username(char *buf) {
    sprintf(buf, "user%d", rand_range(1000, 9999));
}

void fake_word(char *buf) {
    const char *words[] = {"alpha", "beta", "gamma", "delta", "omega"};
    strcpy(buf, words[rand() % 5]);
}

// CASE GENERATORS

void social_post_case(FILE *fp, int index) {
    SocialPost p;

    sprintf(p.content, "This is fake content post number %d", index);
    sprintf(p.image_url, "https://picsum.photos/seed/%d/600/400", index);
    p.likes_count = rand_range(0, 5000);
    p.comments_count = rand_range(0, 1000);
    p.user_id = rand_range(1000, 9999);
    fake_username(p.username);

    sprintf(
        p.user_avatar,
        "https://randomuser.me/api/portraits/%s/%d.jpg",
        (rand() % 2) ? "men" : "women",
        rand_range(1, 99)
    );

    fprintf(fp,
        "\"%s\",\"%s\",%d,%d,%d,\"%s\",\"%s\"\n",
        p.content,
        p.image_url,
        p.likes_count,
        p.comments_count,
        p.user_id,
        p.username,
        p.user_avatar
    );
}

void ecommerce_product_case(FILE *fp, int index) {
    Product p;

    sprintf(p.product_id, "P-%05d", index);
    fake_word(p.product_name);
    fake_word(p.category);
    p.price = rand_double(5, 500);
    p.stock = rand_range(0, 1000);
    p.rating = rand_double(1, 5);

    fprintf(fp,
        "\"%s\",\"%s\",\"%s\",%.2f,%d,%.1f\n",
        p.product_id,
        p.product_name,
        p.category,
        p.price,
        p.stock,
        p.rating
    );
}

void user_profile_case(FILE *fp, int index) {
    UserProfile u;

    u.user_id = index;
    sprintf(u.name, "User %d", index);
    sprintf(u.email, "user%d@example.com", index);
    strcpy(u.country, "USA");
    strcpy(u.signup_date, "2022-01-01");
    u.is_active = rand() % 2;

    fprintf(fp,
        "%d,\"%s\",\"%s\",\"%s\",\"%s\",%d\n",
        u.user_id,
        u.name,
        u.email,
        u.country,
        u.signup_date,
        u.is_active
    );
}

//CASE REGISTRY

typedef void (*CaseFn)(FILE *, int);

typedef struct {
    const char *name;
    const char *header;
    CaseFn fn;
} CaseEntry;

CaseEntry CASE_REGISTRY[] = {
    {
        "social_posts",
        "content,image_url,likes_count,comments_count,user_id,username,user_avatar",
        social_post_case
    },
    {
        "ecommerce_products",
        "product_id,product_name,category,price,stock,rating",
        ecommerce_product_case
    },
    {
        "user_profiles",
        "user_id,name,email,country,signup_date,is_active",
        user_profile_case
    }
};

int CASE_COUNT = sizeof(CASE_REGISTRY) / sizeof(CASE_REGISTRY[0]);

// CSV GENERATION ENGINE

void generate_csv(
    const char *case_name,
    const char *filename,
    int row_count,
    unsigned int seed
) {
    srand(seed);

    CaseEntry *selected = NULL;

    for (int i = 0; i < CASE_COUNT; i++) {
        if (strcmp(CASE_REGISTRY[i].name, case_name) == 0) {
            selected = &CASE_REGISTRY[i];
            break;
        }
    }

    if (!selected) {
        fprintf(stderr, "Unknown case '%s'\n", case_name);
        exit(1);
    }

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Failed to open file");
        exit(1);
    }

    fprintf(fp, "%s\n", selected->header);

    for (int i = 1; i <= row_count; i++) {
        selected->fn(fp, i);
    }

    fclose(fp);

    printf("✅ '%s' created with %d rows using case '%s'\n",
           filename, row_count, case_name);
}

// Main 

int main(void) {
    generate_csv("social_posts", "social_posts.csv", 100, 42);
    generate_csv("ecommerce_products", "products.csv", 50, 123);
    generate_csv("user_profiles", "users.csv", 25, 999);

    return 0;
}
