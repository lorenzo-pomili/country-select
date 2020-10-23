type faIcon;

[@bs.module "@fortawesome/free-solid-svg-icons"] [@bs.val]
external faSearch: faIcon = "faSearch";

[@bs.module "@fortawesome/react-fontawesome"] [@react.component]
external make: (~icon: faIcon, ~className: option(string)) => React.element =
  "FontAwesomeIcon";
