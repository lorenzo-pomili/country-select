type childrenProps = {
  index: int,
  style: ReactDOMStyle.t,
};

[@bs.module "react-window"] [@react.component]
external make:
  (
    ~itemSize: int,
    ~height: string,
    ~itemCount: int,
    ~initialScrollOffset: int,
    ~children: childrenProps => React.element
  ) =>
  React.element =
  "FixedSizeList";
