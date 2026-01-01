# Scalable CSV Data Generator (Python & C)

A scalable, case-based CSV data generator implemented in **both Python and C**.
This repository demonstrates the same data-generation architecture across two
languages, allowing users to choose between rapid development (Python) and
high-performance, dependency-free execution (C).

---

## 🚀 Features

- Case-based dataset generation (schema-driven)
- Multiple language implementations (Python & C)
- Memory-efficient CSV streaming
- Deterministic output using random seeds
- Easily extensible with new data cases
- MIT Licensed

---

## 🧩 Implementations

### 🐍 Python Version
- Uses the `faker` library for realistic synthetic data
- High-level, easy to extend
- Best for rapid prototyping and data science workflows

### ⚙️ C Version
- Zero external dependencies
- High performance and low memory usage
- Suitable for embedded systems, large-scale batch jobs, and environments
  where Python is unavailable

Both versions share the same design philosophy and supported cases.

---

## 📂 Supported Data Cases

| Case Name | Description |
|---------|-------------|
| `social_posts` | Synthetic social media post data |
| `ecommerce_products` | E-commerce product catalog data |
| `user_profiles` | User profile and account data |

---
