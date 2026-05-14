import random
from datetime import datetime, timedelta
import os

services = ["AuthService", "UIService", "DBService", "PaymentService", "ReportService", "System"]
levels = ["INFO", "WARNING", "ERROR"]
messages = {
    "INFO": ["User login sukses", "Backup selesai", "Data sinkron", "Payment berhasil"],
    "WARNING": ["Koneksi lambat", "Salah password", "Disk 80%", "Latensi naik"],
    "ERROR": ["API Timeout", "Database Down", "Memory Leak", "SSL Expired"]
}

def tambah_data_dummy(filename, count, start_id):
    start_date = datetime(2026, 1, 1)
    end_date = datetime(2026, 12, 31)
    seconds_range = int((end_date - start_date).total_seconds())

    try:
        os.makedirs(os.path.dirname(filename), exist_ok=True) if os.path.dirname(filename) else None

        with open(filename, "a", encoding="utf-8") as f:
            for i in range(start_id, start_id + count):
                random_sec = random.randint(0, seconds_range)
                ts = (start_date + timedelta(seconds=random_sec)).strftime("%Y-%m-%d %H:%M:%S")
                lv = random.choice(levels)
                srv = random.choice(services)
                msg = random.choice(messages[lv])

                line = f"{i}|{ts}|{lv}|{srv}|{msg}\n"
                f.write(line)

        print(f"\nMantap! Data berhasil ditambah ke: {filename}")

    except Exception as e:
        print(f"Gagal nambah data karena: {e}")

# tambah_data_dummy(lokasi file/nama file, berapa banyak data, mulai dari id berapa)
tambah_data_dummy("output/data_log.txt", 15000, 1)