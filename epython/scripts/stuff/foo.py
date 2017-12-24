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
    
    print (sys.modules)
    print(ryan_engine.__dict__);
    print("plus:%s"%ryan_engine.plus(2,3))
    print("minus:%s"%ryan_engine.minus(2,3))
    print("TEST_MESSAGE:%s"%ryan_engine.TEST_MESSAGE)
    print(ryan_engine.plus.__module__)
    print(ryan_engine.plus.__name__)
    print(ryan_engine.plus.__doc__)
    print(ryan_engine.plus.__class__)

    print(ryan_engine.Actor.__name__)
    class MyActor(ryan_engine.Actor):
        pass
    ryan_engine.Actor.speak()
    
    MyActor.speak()
    myActor = MyActor()
    myActor.speak()
    print(dir(myActor))
    print(isinstance(myActor, ryan_engine.Actor))
    print(dir(ryan_engine.Actor))

print("Foo loaded")
bar = Foo
