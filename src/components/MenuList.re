module Style = {
  open Css;
  let scroll =
    style([
      width(230->px),
      borderBottomLeftRadius(2->px),
      borderBottomRightRadius(2->px),
      boxShadow(StyleCommon.containerShadow),
      backgroundColor("ffffff"->hex),
      boxSizing(`contentBox),
    ]);
};

let itemSize = StyleCommon.optionHeight;

[@react.component]
let make = (~props: ReactSelect.MenuList.menuListProps) => {
  let selectedValues = props.getValue();
  let initialOffset =
    switch (selectedValues) {
    | None => 0
    | Some(opts) =>
      props.options
      ->Belt.Array.getIndexBy(o =>
          switch (opts->Belt.Array.get(0)) {
          | None => false
          | Some(o2) => o2.value === o.value
          }
        )
      ->Belt.Option.getWithDefault(0)
      * itemSize
    };

  let numOfChildren = props.children->Belt.Array.length;
  let childrenHeight = numOfChildren * itemSize;

  let height =
    childrenHeight < props.maxHeight ? childrenHeight : props.maxHeight;
  numOfChildren > 0
    ? <FixedSizeList
        itemSize
        className=Style.scroll
        height
        itemCount={props.children->Belt.Array.length}
        initialScrollOffset=initialOffset>
        {({style, index}) => {
           <div style>
             {switch (props.children->Belt.Array.get(index)) {
              | None => React.null
              | Some(e) => e
              }}
           </div>;
         }}
      </FixedSizeList>
    : ReactSelect.NoOptionsMessage.make(props);
};
