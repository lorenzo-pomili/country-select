module Style = {
  open Css;

  let activator =
    style([
      width(119->px),
      height(26->px),
      borderRadius(3->px),
      border(1->px, `solid, rgba(0, 0, 0, `num(0.2))),
      backgroundColor("ffffff"->hex),
      cursor(`pointer),
      focus([
        backgroundColor("cccccc"->hex),
        outline(0->px, `none, "ffffff"->hex),
      ]),
    ]);

  let content =
    style([
      display(`flex),
      marginBottom(4->px),
      marginTop(4->px),
      marginLeft(10->px),
    ]);

  let text =
    style([
      display(`inlineBlock),
      width(85->px),
      height(18->px),
      fontFamily(`custom("Arial")),
      fontSize(14->px),
      fontWeight(`normal),
      fontStyle(`normal),
      lineHeight(`abs(1.29)),
      letterSpacing(`normal),
      color("333333"->hex),
      boxSizing(`borderBox),
    ]);

  let arrow =
    style([
      display(`inlineBlock),
      marginLeft(6->px),
      width(8->px),
      height(8->px),
      objectFit(`contain),
    ]);
};

let arrowDown =
  <svg viewBox="0 0 100 100"> <polygon points="50 75, 100 0, 0 0" /> </svg>;

[@react.component]
let make = (~text, ~onClick, ~activatorRef) => {
  <div
    className=Style.activator
    onClick
    ref={ReactDOM.Ref.domRef(activatorRef)}
    tabIndex=0>
    <div className=Style.content>
      <span className={Style.text ++ " " ++ StyleCommon.ellipsis}>
        text->React.string
      </span>
      <span className=Style.arrow> arrowDown </span>
    </div>
  </div>;
};
