[@bs.val] external requireCss: string => unit = "require";

requireCss("node_modules/flag-icon-css/css/flag-icon.min.css");

module Style = {
  open Css;

  let container =
    style([display(`flex), height(StyleCommon.optionHeight->px)]);

  let flag =
    style([
      display(`inlineBlock),
      width(14->px)->important,
      height(10->px),
      marginLeft(10->px),
      marginTop(8->px),
    ]);

  let label =
    style([
      display(`inlineBlock),
      width(182->px),
      height(18->px),
      fontFamily(`custom("Arial")),
      fontSize(14->px),
      fontWeight(`normal),
      // fontStretch(`normal),
      fontStyle(`normal),
      lineHeight(`abs(1.29)),
      letterSpacing(`normal),
      color("333333"->hex),
      marginTop(4->px),
      marginLeft(8->px),
      marginRight(16->px),
    ]);
};

[@react.component]
let make = (~countryCode, ~children) =>
  <div className=Style.container>
    <span
      className={
        "flag-icon flag-icon-"
        ++ countryCode
        ++ " flag-icon-squared "
        ++ Style.flag
      }
    />
    <label className={Style.label ++ " " ++ StyleCommon.ellipsis}>
      children
    </label>
  </div>;
