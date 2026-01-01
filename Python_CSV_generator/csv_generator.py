import csv
import random
from faker import Faker
from typing import Dict, Callable

fake = Faker()

# CASE Generators

def social_post_case(index: int) -> Dict:
    """Generate a social media post row"""
    return {
        "content": fake.sentence(nb_words=10),
        "image_url": f"https://picsum.photos/seed/{index}/600/400",
        "likes_count": random.randint(0, 5000),
        "comments_count": random.randint(0, 1000),
        "user_id": random.randint(1000, 9999),
        "username": fake.user_name(),
        "user_avatar": (
            f"https://randomuser.me/api/portraits/"
            f"{random.choice(['men', 'women'])}/{random.randint(1, 99)}.jpg"
        ),
    }


def ecommerce_product_case(index: int) -> Dict:
    """Generate an e-commerce product row"""
    return {
        "product_id": f"P-{index:05d}",
        "product_name": fake.word().capitalize(),
        "category": fake.word(),
        "price": round(random.uniform(5, 500), 2),
        "stock": random.randint(0, 1000),
        "rating": round(random.uniform(1, 5), 1),
    }


def user_profile_case(index: int) -> Dict:
    """Generate a user profile row"""
    return {
        "user_id": index,
        "name": fake.name(),
        "email": fake.email(),
        "country": fake.country(),
        "signup_date": fake.date_this_decade(),
        "is_active": random.choice([True, False]),
    }


# CASE REGISTRY

CASE_REGISTRY: Dict[str, Callable[[int], Dict]] = {
    "social_posts": social_post_case,
    "ecommerce_products": ecommerce_product_case,
    "user_profiles": user_profile_case,
}

# CSV GENERATION ENGINE

def generate_csv(
    case_name: str,
    filename: str,
    row_count: int = 100,
    seed: int | None = None,
):
    if case_name not in CASE_REGISTRY:
        raise ValueError(f"Unknown case '{case_name}'. Available: {list(CASE_REGISTRY)}")

    if seed is not None:
        random.seed(seed)
        Faker.seed(seed)

    row_generator = CASE_REGISTRY[case_name]

    # Generate first row to get headers
    first_row = row_generator(1)

    with open(filename, "w", newline="", encoding="utf-8") as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=first_row.keys())
        writer.writeheader()
        writer.writerow(first_row)

        for i in range(2, row_count + 1):
            writer.writerow(row_generator(i))

    print(f"✅ '{filename}' created with {row_count} rows using case '{case_name}'")

