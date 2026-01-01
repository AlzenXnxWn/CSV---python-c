#include <stdio.h>

// generate_csv is already defined in csv_generator.c 

int main(void) {
    // Generate 100 social media posts 
    generate_csv(
        "social_posts",
        "social_posts.csv",
        100,
        42
    );

    // Generate 50 e-commerce products 
    generate_csv(
        "ecommerce_products",
        "products.csv",
        50,
        123
    );

    // Generate 25 user profiles 
    generate_csv(
        "user_profiles",
        "users.csv",
        25,
        999
    );

    return 0;
}
