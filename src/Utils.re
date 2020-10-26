let focusRef = (elRef: React.ref(Js.Nullable.t(Dom.element))) =>
  switch (elRef.current->Js.Nullable.toOption) {
  | None => ()
  | Some(c) => ReactDOM.domElementToObj(c)##focus()
  };
