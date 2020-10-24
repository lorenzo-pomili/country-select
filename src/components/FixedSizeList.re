type childrenProps = {
  index: int,
  style: ReactDOMStyle.t,
};

[@bs.module "react-window"] [@react.component]
external make:
  (
    ~itemSize: int,
    ~className: string,
    ~height: int,
    ~itemCount: int,
    ~initialScrollOffset: int,
    ~children: childrenProps => React.element
  ) =>
  React.element =
  "FixedSizeList";
