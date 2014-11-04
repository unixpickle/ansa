// This script generates the contents of numeric-info.hpp

void main() {
  print('template <>');
  printSignedType('signed char', 'unsigned char');
  print('template <>');
  printUnsignedType('char');
  print('template <>');
  printPlainCharType();
  for (var name in ['short', 'int', 'long', 'long long']) {
    print('template <>');
    printSignedType(name);
    print('template <>');
    printUnsignedType(name);
  }
}

void printSignedType(String name, [String _unsignedName = null]) {
  var unsignedName = (_unsignedName == null ? name : _unsignedName);
  print("""
struct NumericInfo<$name> {
  static constexpr size_t size = sizeof($name);
  static constexpr size_t bitCount = size * 8;
  static constexpr $name min =
      ($name)1 << (bitCount - 1);
  static constexpr $name max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "$name";
  typedef $name SignedType;
  typedef $unsignedName UnsignedType;
};
""");
}

void printUnsignedType(String name) {
  print("""
struct NumericInfo<unsigned $name> {
  static constexpr size_t size = sizeof(unsigned $name);
  static constexpr size_t bitCount = size * 8;
  static constexpr unsigned $name max = ~(unsigned $name)0;
  static constexpr unsigned $name min = (unsigned $name)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned $name";
  typedef $name SignedType;
  typedef unsigned $name UnsignedType;
};
""");
}

void printPlainCharType() {
  print("""
struct NumericInfo<char> {
  static constexpr bool isSigned = (char)-1 < (char)0;
  static constexpr size_t size = sizeof(char);
  static constexpr size_t bitCount = size * 8;
  static constexpr char max = isSigned ? NumericInfo<signed char>::max :
                              NumericInfo<unsigned char>::max;
  static constexpr char min = isSigned ? NumericInfo<signed char>::min :
                              NumericInfo<unsigned char>::min;
  static constexpr const char * name = "char";
  typedef signed char SignedType;
  typedef unsigned char UnsignedType;
};
""");
}

