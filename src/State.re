module type S = {
  type t(_);

  type state;

  module Monad_instance: MonadClass.S with type t('a) = t('a);

  module Monad: (module type of MonadClass.Extend(Monad_instance));

  module Functor_instance: (module type of
    FunctorClass.Of_monad(Monad_instance));

  let run: (state, t('a)) => (state, 'a);

  let get: t(state);

  let set: state => t(unit);

  let modify: (state => state) => t(unit);
};

module Make = (K: {type t;}) : (S with type state := K.t) => {
  module Run = {
    type t('a) = K.t => (K.t, 'a);
  };

  type t('a) = Run.t('a);

  let run = (k, ma) => ma(k);

  module Monad_instance = {
    type t('a) = Run.t('a);

    let pure = (a, k) => (k, a);

    let bind = (f, ma, k) => {
      let (k2, a) = ma(k);
      (f(a))(k2);
    };
  };

  module Monad = MonadClass.Extend(Monad_instance);

  module Functor_instance = FunctorClass.Of_monad(Monad_instance);

  let get = k => (k, k);

  let set = (k, _) => (k, ());

  let modify = f => Monad.(get >>= (k => set(f(k))));
};
