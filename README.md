### MAZE

This program prints a random generated maze.  It works using the
first depth recursive algorithm.  Is't right now in working in
progress status, as by now, there's only a fixed test main
program.

The kind of mazes it creates is like the one shown below:

    ┌─┬─────┬───┬───────┬───────────┬───────┐
    │ │ ┌─╴ │ ╷ │ ╶─────┘ ┌─╴ ┌───┐ ╵ ┌───┐ │
    │ │ └─┐ ╵ │ └───┬───┐ │ ╶─┼─╴ ├───┴─╴ │ │
    │ └─┐ └───┼───┐ ╵ ╷ └─┼─╴ │ ╶─┘ ╷ ╶───┤ │
    ├─┐ │ ┌─╴ │ ╶─┴───┴─╴ ╵ ┌─┘ ╶───┴───┐ ╵ │
    │ │ ├─┘ ┌─┼─────────────┴─────┬───┐ └───┤
    │ │ ╵ ┌─┘ │                   │ ╷ ├───┐ │
    │ └─┬─┴─╴ │                   │ │ ╵ ╷ ╵ │
    │ ╷ ╵ ╷ ╶─┤                   │ ├───┴───┤
    │ └─┬─┴─╴ │                   │ │ ┌───┐ │
    ├─╴ │ ╶─┐ │                   │ └─┤ ╷ ╵ │
    ├───┴─┐ │ │                   ├─╴ │ ├─╴ │
    │ ┌─╴ │ └─┤                   │ ┌─┘ │ ╶─┤
    │ │ ┌─┴─╴ │                   │ ╵ ┌─┼─╴ │
    │ │ ╵ ┌─╴ │                   ├─┬─┘ ╵ ┌─┤
    │ ├───┴───┴─┬───┬───────────┬─┘ │ ╶─┬─┘ │
    │ │ ╶───┐ ╷ │ ╷ └─┐ ╶─┬───╴ │ ╷ └─╴ │ ╶─┤
    │ ├───╴ │ │ ╵ ├─╴ └─╴ ├───┬─┘ ├─────┴─╴ │
    │ │ ╶───┤ ├───┼─────┬─┘ ╷ ╵ ┌─┘ ╶─┬───┐ │
    │ └───╴ │ ╵ ╷ ╵ ╶─┐ ╵ ╶─┴───┴───╴ │ ╷ ╵ │
    └───────┴───┴─────┴───────────────┴─┴───┘

 but by now, there's no options handling code, so it only
 generates the above maze.
