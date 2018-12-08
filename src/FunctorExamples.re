module OptionFunctor: FunctorClass.S with type t('a) = option('a) = {
  type t('a) = option('a);

  let map = f =>
    fun
    | None => None
    | Some(a) => Some(f(a));
};
