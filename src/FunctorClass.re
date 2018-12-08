module type S = {
  type t(_);

  let map: ('a => 'b, t('a)) => t('b);
};

module Of_monad = (M: MonadClass.S) : (S with type t('a) = M.t('a)) => {
  type t('a) = M.t('a);

  let map = (f, ma) => M.bind(a => M.pure(f(a)), ma);
};
