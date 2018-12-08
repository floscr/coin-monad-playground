module type S = {
  type t(_);

  let pure: 'a => t('a);

  let bind: ('a => t('b), t('a)) => t('b);
};

module type EXTENSION = {
  type t(_);

  include S with type t('a) := t('a);

  let (>>=): (t('a), 'a => t('b)) => t('b);

  let join: t(t('a)) => t('a);

  let sequence: list(t('a)) => t(list('a));
};

module Extend = (M: S) : (EXTENSION with type t('a) := M.t('a)) => {
  include M;

  let (>>=) = (m, f) => M.bind(f, m);

  let join = maa => maa >>= (ma => ma);

  let sequence = mas =>
    List.fold_right(
      (ma, ms) => ma >>= (a => ms >>= (s => pure([a, ...s]))),
      mas,
      pure([]),
    );
};
