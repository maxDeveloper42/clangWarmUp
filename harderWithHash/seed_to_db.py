#!/usr/bin/env python3
import random

FIRST = ["Alice", "Bob", "Carol", "David", "Eve", "Frank", "Grace", "Henry",
         "Ivy", "Jack", "Kate", "Leo", "Mia", "Noah", "Olivia", "Paul",
         "Quinn", "Ryan", "Sophia", "Tom", "Uma", "Victor", "Wendy", "Xander",
         "Yara", "Zack"]

LAST = ["Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller",
        "Davis", "Rodriguez", "Martinez", "Hernandez", "Lopez", "Gonzalez",
        "Wilson", "Anderson", "Thomas", "Taylor", "Moore", "Jackson", "Martin"]

def random_phone():
    return f"{random.randint(100,999)}-{random.randint(100,999)}-{random.randint(1000,9999)}"

def generate_db(filename="contacts.db", count=50, mode="w"):
    with open(filename, mode) as f:
        for _ in range(count):
            name = f"{random.choice(FIRST)} {random.choice(LAST)}"
            phone = random_phone()
            f.write(f"{name},{phone}\n")
    print(f"Wrote {count} contacts to {filename}")

if __name__ == "__main__":
    # Change count here if you want more/less
    generate_db(count=50)
