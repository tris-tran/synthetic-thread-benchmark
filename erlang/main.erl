-module(main).

-export([ start/1, busy_thread/0 ]).

busy_thread() ->
    receive
        start ->
            busy_work(),
            main_thread ! finished

    end.

busy_work(_, Time) when Time >= 10000 ->
    done;
busy_work(Start, _) ->
    work(1000),
    busy_work(Start, erlang:system_time(millisecond) - Start).
busy_work() ->
    Start = erlang:system_time(millisecond),
    busy_work(Start, 0).

work(0) ->
    done;
work(I) -> 
    work(I-1).

start_pids([]) ->
    done;
start_pids([Head | Rest]) ->
    Head ! start,
    start_pids(Rest)
    .

await_pids(0) ->
    done;
await_pids(PidCount) ->
    receive
        finished ->
            await_pids(PidCount - 1)
    end.

start(0, AccList) ->
    io:get_line("All threads waiting run\n"),
    start_pids(AccList),
    await_pids(length(AccList));
start(Threads, AccList) -> 
    Busy_pid = spawn(main, busy_thread, []),
    start(Threads - 1, [Busy_pid | AccList])
    .
start(Threads) ->
    register(main_thread, self()),
    Busy_pid = spawn(main, busy_thread, []),
    start(Threads - 1, [Busy_pid]).

