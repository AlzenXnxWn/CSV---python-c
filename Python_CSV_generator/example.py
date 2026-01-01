
# EXAMPLE USAGE of the code in file<csv_1_socialmedia.py>

if __name__ == "__main__":
    generate_csv(
        case_name="social_posts",
        filename="social_posts.csv",
        row_count=1000,
        seed=42,
    )

    generate_csv(
        case_name="ecommerce_products",
        filename="products.csv",
        row_count=500,
    )

    generate_csv(
        case_name="user_profiles",
        filename="users.csv",
        row_count=300,
    )
