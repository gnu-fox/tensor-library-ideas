#include <iostream>
#include <memory>

// The std::align function is used to align a pointer to a given alignment.
// The function returns a pointer to the first byte of the next block of storage,
// if the alignment is successful. Otherwise, it returns a null pointer.
// The function also updates the value of the second parameter to reflect the
// remaining storage available at the returned pointer.
// The function has the following signature:
// void* align(std::size_t alignment, std::size_t size, void*& ptr, std::size_t& space);
// The first parameter is the alignment value.
// The second parameter is the size of the block of storage.
// The third parameter is a reference to a pointer to the block of storage.
// The fourth parameter is a reference to the remaining storage available at the returned pointer.
// The function returns a pointer to the first byte of the next block of storage, if the alignment is successful.
// Otherwise, it returns a null pointer.

int main() {
  char buffer[] = "------------------------";
  void * pt = buffer;
  std::size_t space = sizeof(buffer)-1;
  std::cout << space << '\n';

  while ( std::align(alignof(int),sizeof(char),pt,space) ) {
  
    char* temp = static_cast<char*>(pt);
  
    *temp='*'; ++temp; space-=sizeof(char);
  
    pt=temp;
  }
  std::cout << buffer << '\n';
  return 0;
}