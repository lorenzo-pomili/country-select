[@bs.val] external requireCss: string => unit = "require";

requireCss("node_modules/flag-icon-css/css/flag-icon.min.css");

[@react.component]
let make = (~countryCode, ~children) =>
  <div>
    <span
      className={"flag-icon flag-icon-" ++ countryCode ++ " flag-icon-squared"}
    />
    children
  </div>;
