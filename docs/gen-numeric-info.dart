// This script generates the contents of numeric-info.hpp

void main() {
  for (var name in ['char', 'short', 'int', 'long', 'long long']) {
    print('template <>');
    printSignedType(name);
    print('template <>');
    printUnsignedType(name);
  }
}

void printSignedType(String name) {
  print("""
struct NumericInfo<$name> {
  static constexpr int size = sizeof($name);
  static constexpr int bitCount = size * 8;
  static constexpr $name min =
      ($name)1 << (bitCount - 1);
  static constexpr $name max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "$name";
};
  """);
}

void printUnsignedType(String name) {
  print("""
struct NumericInfo<unsigned $name> {
  static constexpr int size = sizeof(unsigned $name);
  static constexpr int bitCount = size * 8;
  static constexpr unsigned $name max = ~(unsigned $name)0;
  static constexpr unsigned $name min = (unsigned $name)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned $name";
};
  """);
}

