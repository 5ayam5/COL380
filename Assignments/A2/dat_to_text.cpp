#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

int read(std::ifstream &file) {
  unsigned char buffer[4];
  file.read((char *)buffer, sizeof(buffer));
  return (int)buffer[3] | (int)buffer[2] << 8 | (int)buffer[1] << 16 |
         (int)buffer[0] << 24;
}
int main(int argc, char *argv[]) {
  assert(argc > 1);
  int numbers = std::stoi(argv[1]);
  std::string file = "output.dat";
  if (argc > 2)
    file = argv[2];

  std::ifstream fs(file, std::ios::binary);
  if (numbers == -1) {
    int beg = fs.tellg();
    fs.seekg(0, std::ios::end);
    numbers = ((int)fs.tellg() - beg) / 4;
    fs.seekg(0, std::ios::beg);
  }
  while (numbers--)
    std::cout << read(fs) << '\n';
}
