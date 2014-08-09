# Abstract

Linked lists are a crucial data structure for almost any application. However, doubly-linked lists can be a bit of a pain to reimplement again and again. The `LinkedList<T>` class provides a drop-in linked list implementation for pretty much any application.

# Usage

In some libraries, I've seen a LinkedListNode class or the likes which you must subclass in an element object. I don't like that model, because it limits your object to one linked list at a time. Instead, I propose the following model:

You have a class, `MyElement` that you would like to put in a linked list. So, you will use the linked list type `ansa::LinkedList<MyElement>`. But how will the linked list...you know...link `MyElement` objects together? This is where the fun part comes in: just add an instance variable to `MyElement` of the type `ansa::LinkedList<MyElement>::Link`. Let's call that field `link`.

We can use a pointer to our `link` field to add and remove instances of `MyElement` to and from a linked list. In `MyElement`'s constructor, we must initialize `link` with a pointer to `this` (e.g. `MyElement() : link(*this) ...`).

You may see [test-linked-list.cpp](../test/test-linked-list.cpp) for a more detailed example of exactly how to perform operations on a linked list.
