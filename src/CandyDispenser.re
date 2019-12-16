type input =
  | Insert_coin
  | Turn;

module Machine_state = {
  type t = {
    locked: bool,
    candies: int,
    coins: int,
  };
};

type t = Machine_state.t;

let make = (~candies, ~coins) =>
  Machine_state.{locked: true, candies, coins};

module Machine = State.Make(Machine_state);

let insert_coin =
  Machine.modify(s =>
    Machine_state.(
      if (s.locked && s.coins > 0) {
        {...s, locked: false, coins: s.coins + 1};
      } else {
        s;
      }
    )
  );

let turn =
  Machine.modify(s =>
    Machine_state.(
      if (s.locked) {
        s;
      } else {
        {...s, locked: true, candies: s.candies - 1};
      }
    )
  );

let next = input =>
  Machine_state.(
    Machine.Monad.(
      Machine.get
      >>= (
        s =>
          if (s.candies == 0) {
            pure();
          } else {
            switch (input) {
            | Turn => turn
            | Insert_coin => insert_coin
            };
          }
      )
    )
  );

let run = (inputs, t) =>
  Machine_state.(
    Machine.Monad.sequence(List.map(next, inputs))
    |> Machine.run(t)
    |> fst
    |> (s => (s.candies, s.coins))
  );
