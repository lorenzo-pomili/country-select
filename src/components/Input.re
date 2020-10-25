module Style = {
  open Css;

  let inputContainer =
    style([
      display(`inlineBlock),
      marginLeft(10->px),
      boxSizing(`borderBox),
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
let make = (~props: ReactSelect.Input.inputProps) =>
  <div className=Style.inputContainer>
    <div className=Style.iconContainer>
      <FontAwesomeIcon
        className={Some(Style.icon)}
        icon=FontAwesomeIcon.faSearch
      />
    </div>
    <span className=Style.input> {ReactSelect.Input.make(props)} </span>
  </div>;
