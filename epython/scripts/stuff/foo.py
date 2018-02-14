class Foo(object):
    def __init__(self):
        print("fooooo")
    def ok(self):
        pass
def barz():
    pass

import sys
print(sys.modules)
try:
    import ryan_engine
except ImportError:
    print("no ryan_engine")
else:
    print("ryan_engine is here!!")
    
    print(sys.modules)
    print(ryan_engine.__dict__)
    print("plus:%s" % ryan_engine.plus(2,3))
    print("minus:%s" % ryan_engine.minus(2,3))
    print("TEST_MESSAGE:%s" % ryan_engine.TEST_MESSAGE)
    print(ryan_engine.plus.__module__)
    print(ryan_engine.plus.__name__)
    print(ryan_engine.plus.__doc__)
    print(ryan_engine.plus.__class__)

    print(ryan_engine.Actor.__name__)
    print("defing MyActor")
    class MyActor(ryan_engine.Actor):
        def __init__(self, name, n):
            super(MyActor, self).__init__(n)
            self.name = name

        def private_speak(self):
            super(MyActor, self).private_speak()
            print("hello from %s" % self.name)
            print(self)

        def nonono(self):
            print("nonono")

        def tell_me(self):
            rr = super(MyActor, self).tell_me()
            return self.name, rr

    print(issubclass(MyActor, ryan_engine.Actor))
    ryan_engine.Actor.speak()
    # ryan_engine.Actor.private_speak()
    
    for i in range(1):
        print(ryan_engine.Actor(i).tell_me())
        print(MyActor("%10d" % i, i).tell_me())
        
    MyActor.speak()
    print(type(MyActor))
    myActor = MyActor("SUPERNAME", 33)
    print(myActor.TEST_VAR)
    print(myActor.TEST_VAR)
    myActor.speak()
    myActor.private_speak()
    print(myActor.tell_me())
    print(type(myActor))
    print(isinstance(myActor, MyActor))
    print(dir(myActor))
    myActor.nonono()
    print(isinstance(myActor, ryan_engine.Actor))
    print(dir(ryan_engine.Actor))

print("Foo loaded")
bar = Foo
