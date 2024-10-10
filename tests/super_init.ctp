# Test Output: 5555.0one

include <map>
include <string>

class (Generic:
    x  # implicit 1-arg constructor, deleted 0-arg constructor
)

class (Concrete(Generic):
    def (init, x: int:
        super.init(x)
    )
)

class (Generic2(Generic):
    y
    def (init, x, y:
        self.y = y
        super.init(x)
    )
)

class (Concrete2(Concrete):
    # no user defined init - inherits constructors
    pass
)

def (main:
    f = Generic("5")
    f2 = Concrete(5)
    #f2e = Concrete("5")  # error
    f3 = Generic2([5, 6], std.map<int, std.string> { {1, "one"} })
    f4 = Concrete2(42)
    std.cout << f.x << f2.x << f3.x[0] << f3.y.at(1) << f4.x
)
