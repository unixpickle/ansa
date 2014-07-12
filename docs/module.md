# Abstract

In an operating system or some other large program, you may benefit from a runtime dependency initialization tool. The module API provides exactly this.

Each module has an `Initilaize()` method. This is the body of the module initialization. Each module also has a set of dependencies. By the time a module's `Initialize()` method is called, all of it's dependencies will have been loaded.

## "Super dependencies"

Sometimes, a module might depend on some other module to configure a temporary state before it's own `Initialize()` method. As an example, suppose *module A* lists *module B* as a dependency so that *module B* can setup a temporary memory allocator that *module A* will use to configure the permanent memory allocator. If *module A* is loaded first&ndash;because, for instance, it is listed as a dependency for the root module&ndash;everything will go fine.

However, suppose that *module B* is initialized directly as a dependency of some other module. Now, a temporary memory allocator is in place that is meant only to be used by *module A*. This problem is solved by defining super dependencies. In this case, *module B* would list *module A* as a super dependency. This means that directly after *mobule B* is initialized, *module A* will also be initialized.

## Specifics

To load a module, you simply call it's `Load()` method. This will load the module's dependencies, call it's `Initialize()` method, and then load it's super dependencies. If a module's `Load()` method has been called before, calling `IsUninitialized()` on it will return `false`. If a module has been completely initailized (with dependencies and super dependencies), it's `IsInitialized()` method will return `true`. Note the subtle difference between these two methods.

A module returns its dependencies and super dependencies by overload the `GetDependencies()` and `GetSuperDependencies()` methods respectively. These functions return a `DepList()`, which is super easy to construct:

    DepList MyModule::GetDependencies() {
        return DepList(&SomeOtherModule::GetGlobal(),
                       &CoolModule::GetGlobal())
    }

The `DepList()` constructor uses a variadic template to support a variable argument list.
