class Foo(object):
    def __init__(self):
        print("fooooo")
    def ok(self):
        pass
def barz():
    pass

import sys
print (sys.modules)
try:
    import ryan_engine
except ImportError:
    print("no ryan_engine")
else:
    print("ryan_engine is here!!")
    print(ryan_engine.__dict__);
    print(ryan_engine.hello())
    from ryan_engine import hello
    print(hello());
    print(ryan_engine.hello.__name__)
    print(ryan_engine.print1())
    print(barz.__name__)
    print(Foo.ok.__name__)
    print(Foo().ok.__name__)
print("Foo loaded")
bar = Foo
