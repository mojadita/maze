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

 By default, the maze utility is installed using a prefix of
 ${HOME}, so it is installed on the bin private dir of the user,
 and the manual page is installed in the `man` directory
 hierarchy for the user.  If you want to install it elsewhere,
 you have the possibility to specify the actual directories as
 `make` variables (e.g. `bindir` or `mandir`, or even `prefix`)
 as in:

	 make prefix='/usr/local' install
