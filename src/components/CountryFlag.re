[@react.component]
let make = (~countryCode) =>
  <span
    className={"flag-icon flag-icon-" ++ countryCode ++ " flag-icon-squared"}
  />;
