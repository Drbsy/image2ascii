
# Image to ASCII

This project converts any supported image format into ASCII art.
  
## Usage

Convert an image to ASCII art using:

```bash
./image2ascii <path_to_image> <size> [options]
```

### Size Options

| Size | Flag | Scale Factor |
|---|---|---|
| Small | `-s` | `1/24` |
| Medium | `-m` | `1/12` |
| Large | `-l` | `1/6` |
| Extra Large | `-xl` | `1/3` |
| Extra Extra Large | `-xxl` | `1/1` |
| Custom Line Length | `-llen <size>` | Custom line length size |

### Additional Options

| Option | Flag | Description |
|---|---|---|
| Saliency Threshold | `-salience <val>` or `-sal <val>` | Applies a saliency filter with a custom threshold (e.g., `-sal 140`). |

### Help

To display the help message:

```bash
./image2ascii -h
```

or:

```bash
./image2ascii -help
```

### Supported Image Formats

`jpg`, `jpeg`, `png`, `bmp`, `tga`, `psd`, `hdr`, `pic`, `ppm`, `pgm`

---

## Build

### 1. Install Required Packages

**Arch Linux:**

```bash
sudo pacman -S --needed base-devel git gcc make
```

**Debian / Ubuntu:**

```bash
sudo apt update && sudo apt install -y git gcc make
```

**Fedora:**

```bash
sudo dnf install -y git gcc make
```

### 2. Clone the Repository

```bash
git clone https://github.com/Drbsy/image2ascii.git
```

### 3. Navigate to Directory

```bash
cd image2ascii
```

### 4. Compile

```bash
make
```

---

## Art Examples

![Example 1](https://raw.githubusercontent.com/Drbsy/image2ascii/main/examples/images/2.jpeg)

![Example 2](https://raw.githubusercontent.com/Drbsy/image2ascii/main/examples/images/3.jpeg)

![Example 3](https://raw.githubusercontent.com/Drbsy/image2ascii/main/examples/images/4.jpeg)

![Example 4](https://raw.githubusercontent.com/Drbsy/image2ascii/main/examples/images/5.jpeg)
