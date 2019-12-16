module type X_int = {let x: int;};

module Increment = (M: X_int) : X_int => {
  let x = M.x + 1;
};

module Three = {
  let x = 3;
};

module Three_and_more = {
  let x = 3;
  let y = "three";
};

module type Comparable = {
  type t;
  let compare: (t, t) => int;
};
