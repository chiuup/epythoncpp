"""A sample GameObject script.
"""
from ryan_engine import BaseActor

class Printer(BaseActor):
    """Prints a message every frame
    """
    def __init__(self):
        self.message = None

    def start(self):
        """Called on the frame when a script is enabled
        """
        self.message = "I'm a printer."

    def update(self):
        """Called every frame
        """
        print(self.message)

# This Printer class called "Actor" will be initialized by GameObject
Actor = Printer
