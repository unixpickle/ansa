## ANSA_ALIGNED(x)

This macro is useful for aligning various fields in structures. You place it after the name of a variable or field, like so:

    struct MyStructure {
      int myField ANSA_ALIGNED(8);
    }
    
    static int someStaticValue ANSA_ALIGNED(8) = 3;

## ANSA_PACKED

This macro allows you to pack a structure or class. You put it after the structure body like so:

    struct MyStruct {
      short someField;
      short someOtherField;
      long long anotherField;
    } ANSA_PACKED;

Note that using `ANSA_PACKED` with `ANSA_ALIGNED` could lead to some weird behavior.

## ANSA_NORETURN

Some functions, for example an `exit()` function, will never return to the caller. You may declare a function using this macro as follows in these examples:

    class MyClass {
      virtual Exit() ANSA_NORETURN = 0;
    };
    
    void MyFunction() ANSA_NORETURN;
