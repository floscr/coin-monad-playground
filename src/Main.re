open Printf;

let () = {
  open CandyDispenser;
  let dispenser = make(~candies=10, ~coins=3);
  let (candies, coins) =
    dispenser |> run([Insert_coin, Turn, Insert_coin, Turn, Turn]);
  printf("Got %d candies remaining with %d coins.\n", candies, coins);
};
