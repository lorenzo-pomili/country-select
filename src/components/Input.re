module Style = {
  open Css;

  let inputContainer =
    style([
      display(`inlineBlock),
      marginLeft(10->px),
      boxSizing(`borderBox),
      width(100.->pct),
    ]);

  let iconContainer = style([display(`inlineBlock)]);

  let icon =
    style([
      width(14->px)->important,
      height(14->px),
      objectFit(`contain),
      backgroundColor("ffffff"->hex),
      position(`relative),
    ]);

  let input = style([marginLeft(10->px), display(`inlineBlock)]);
};

[@react.component]
let make =
    (
      ~props: ReactSelect.Input.inputProps,
      ~inputRef: React.ref(Js.Nullable.t(Dom.element)),
    ) => {
  let selectInputRef = React.useRef(Js.Nullable.null);

  React.useEffect1(
    () => {
      inputRef.current = selectInputRef.current;

      None;
    },
    [|inputRef|],
  );

  <div
    className=Style.inputContainer
    onClick={_e => {Utils.focusRef(selectInputRef)}}>
    <div className=Style.iconContainer>
      <FontAwesomeIcon
        className={Some(Style.icon)}
        icon=FontAwesomeIcon.faSearch
      />
    </div>
    <span className=Style.input>
      {ReactSelect.Input.make({
         ...props,
         innerRef: iRef => selectInputRef.current = iRef,
       })}
    </span>
  </div>;
};
