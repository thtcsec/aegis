<div align="center">
  <img src="aegis_banner.png" alt="Aegis Banner" width="600"/>
  
  # Bắt Đầu với Aegis
  
  Hướng dẫn cài đặt và sử dụng Aegis Programming Language
</div>

---

## Yêu Cầu Hệ Thống

- CMake 3.20 trở lên
- Trình biên dịch C++17 (GCC 9+, Clang 10+, MSVC 2019+)
- Thư viện phát triển LLVM 14+

## Cài Đặt LLVM

### Ubuntu/Debian
```bash
sudo apt-get install llvm-14 llvm-14-dev
```

### macOS
```bash
brew install llvm@14
```

### Windows
Tải từ [LLVM Releases](https://releases.llvm.org/)

## Build Dự Án

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Chương Trình Aegis Đầu Tiên

Tạo file `hello.aeg`:

```aegis
fn main() {
    print("Xin chào, Aegis!")
}
```

Chạy chương trình:

```bash
aegis run hello.aeg
```

## Ví Dụ Về Tính Năng Bảo Mật

### Code Không An Toàn (Sẽ Có Cảnh Báo)

```aegis
fn login_khong_an_toan() {
    input user_input
    query = "SELECT * FROM users WHERE name = " + user_input
    execute query  // CẢNH BÁO: tainted input trong SQL query
}
```

Compiler sẽ cảnh báo:
```
warning: tainted input detected in SQL query
  --> login.aeg:3:5
   |
3  |     query = "SELECT * FROM users WHERE name = " + user_input
   |     ^^^^^ dữ liệu không tin cậy được sử dụng trong SQL query
```

### Code An Toàn (Không Có Cảnh Báo)

```aegis
fn login_an_toan() {
    input user_input
    query = sql("SELECT * FROM users WHERE name = ?", user_input)
    execute query  // OK: sử dụng parameterized query
}
```

## Các Tính Năng Bảo Mật Chính

### 1. Taint Analysis (Phân Tích Dữ Liệu Không Tin Cậy)

Aegis tự động theo dõi dữ liệu từ nguồn không tin cậy:

```aegis
input user_data           // Đánh dấu là "tainted"
safe_data = sanitize(user_data)  // Đánh dấu là "sanitized"
```

### 2. SQL Injection Detection

```aegis
// Không an toàn - string concatenation
query = "SELECT * FROM users WHERE id = " + user_id

// An toàn - parameterized query
query = sql("SELECT * FROM users WHERE id = ?", user_id)
```

### 3. Command Injection Detection

```aegis
// Không an toàn
cmd = "ping " + user_input
execute cmd

// An toàn
cmd = command("ping", [user_input])
execute cmd
```

## Cấu Trúc Dự Án Aegis

```
my-project/
├─ src/
│  ├─ main.aeg
│  └─ auth.aeg
├─ tests/
│  └─ test_auth.aeg
└─ aegis.toml
```

## Các Lệnh CLI

```bash
# Biên dịch
aegis build main.aeg

# Chạy
aegis run main.aeg

# Kiểm tra bảo mật
aegis check main.aeg

# Quét lỗ hổng
aegis scan 192.168.1.1 port 80
```

## Ví Dụ Thực Tế

### Web Login An Toàn

```aegis
fn login(username: string, password: string) {
    // Validate input
    if !validate_username(username) {
        return error("Invalid username")
    }
    
    // Sử dụng parameterized query
    query = sql(
        "SELECT * FROM users WHERE username = ? AND password_hash = ?",
        username,
        hash(password)
    )
    
    result = db.execute(query)
    return result
}
```

### Port Scanner

```aegis
fn scan_ports(target: string, start_port: int, end_port: int) {
    for port in range(start_port, end_port) {
        if net.is_open(target, port) {
            print("Port " + port + " is open")
        }
    }
}

fn main() {
    scan_ports("192.168.1.1", 1, 1024)
}
```

## Thư Viện Chuẩn

### std.net - Mạng
```aegis
import std.net

socket = net.connect("example.com", 80)
response = net.http_get("https://example.com")
```

### std.crypto - Mã Hóa
```aegis
import std.crypto

hash = crypto.sha256("data")
encrypted = crypto.aes_encrypt("data", "key")
```

### std.db - Cơ Sở Dữ Liệu
```aegis
import std.db

conn = db.connect("postgresql://localhost/mydb")
result = conn.query("SELECT * FROM users WHERE id = ?", user_id)
```

### std.scan - Quét Bảo Mật
```aegis
import std.scan

scan.port("192.168.1.1", 80)
scan.vuln("https://example.com")
```

## Các Bước Tiếp Theo

1. Đọc [ARCHITECTURE.md](ARCHITECTURE.md) để hiểu kiến trúc compiler
2. Xem thêm ví dụ trong thư mục [examples/](../examples/)
3. Tìm hiểu về security analysis engine
4. Đóng góp vào dự án trên GitHub

## Hỗ Trợ

- **GitHub Repository**: [github.com/thtcsec/aegis](https://github.com/thtcsec/aegis)
- **Issues**: [Báo lỗi hoặc đề xuất tính năng](https://github.com/thtcsec/aegis/issues)
- **Discussions**: [Thảo luận cộng đồng](https://github.com/thtcsec/aegis/discussions)

## Tác Giả

- **Trinh Hoang Tu** ([@thtcsec](https://github.com/thtcsec)) - Người sáng lập & Nhà phát triển chính
- **Aegis Foundation** - Tổ chức duy trì dự án

## Roadmap

- **Phase 1** (Hiện tại): Toy compiler với lexer, parser, interpreter
- **Phase 2**: Type system, module system, LLVM IR
- **Phase 3**: Security analysis hoàn chỉnh (taint analysis, vulnerability detection)
