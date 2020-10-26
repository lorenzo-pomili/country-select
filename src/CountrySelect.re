module Style = {
  open Css;

  let container =
    style([
      width(230->px),
      borderTopLeftRadius(2->px),
      borderTopRightRadius(2->px),
      boxShadow(StyleCommon.containerShadow),
      border(1->px, `solid, rgba(0, 0, 0, `num(0.08))),
      backgroundColor("ffffff"->hex),
    ]);
};

let selectComponentsCustomStyle: option(ReactSelect.customStyles) =
  Some({
    control: () =>
      Js.Dict.fromArray([|
        ("width", "230px"),
        ("height", "35px"),
        ("display", "flex"),
        ("backgroundColor", "rgba(255, 255, 255, 0.08)"),
        ("boxSizing", "border-box"),
      |]),
    valueContainer: base => {
      base->Js.Dict.set("paddingTop", "0px");
      base->Js.Dict.set("paddingBottom", "0px");
      base->Js.Dict.set("paddingLeft", "0px");
      base->Js.Dict.set("paddingRight", "0px");
      base;
    },
    option: (base, _state) => {
      base->Js.Dict.set("padding", "0px");
      base;
    },
    menu: (base, _state) => {
      base->Js.Dict.set("marginTop", "2px");
      base->Js.Dict.set("marginBottom", "0px");
      base->Js.Dict.set("borderRadius", "0px");
      base;
    },
  });

type state =
  | Loading
  | Error
  | Loaded(array(ReactSelect.opt));

let filterOption = (candidate: ReactSelect.opt, input) =>
  input !== ""
    ? Js.String.toLowerCase(input)
      ->Js.String.includes(Js.String.toLowerCase(candidate.label))
    : true;

[@react.component]
let make = (~className, ~country, ~onChange) => {
  let (countries, setCountries) = React.useState(() => Loading);
  let (value, setValue) = React.useState(() => None);
  let (isOpen, setIsOpen) = React.useState(() => false);
  let containerRef = React.useRef(Js.Nullable.null);

  React.useEffect2(
    () => {
      if (isOpen && containerRef.current !== Js.Nullable.null) {
        Utils.focusRef(containerRef);
      };

      None;
    },
    (containerRef, isOpen),
  );

  React.useEffect0(() => {
    let request = GetData.makeXMLHttpRequest();
    GetData.getCountries(
      request,
      cs => {
        switch (country) {
        | None => ()
        | Some(cVal) =>
          setValue(_prev => cs->Belt.Array.getBy(c => c.value === cVal))
        };
        setCountries(_prev => Loaded(cs));
      },
    );

    Some(() => {GetData.abort(request)});
  });

  <div>
    {switch (countries) {
     | Loading => <div> "Loading..."->React.string </div>
     | Error => <div> "Error"->React.string </div>
     | Loaded(cs) =>
       let text =
         switch (value) {
         | None => ""
         | Some(v) => v.label
         };
       <>
         <Activator text onClick={_e => setIsOpen(prev => !prev)} />
         {!isOpen
            ? React.null
            : <div className=Style.container>
                <ReactSelect
                  styles=selectComponentsCustomStyle
                  defaultValue=None
                  value
                  onChange={v => {
                    onChange(v);
                    setValue(_p => Some(v));
                  }}
                  menuIsOpen={Some(true)}
                  components={
                    opt: props =>
                      ReactSelect.Option.make({
                        ...props,
                        children:
                          <CountryFlag countryCode={props.value}>
                            {props.children}
                          </CountryFlag>,
                      }),
                    menuList: props => <MenuList props />,
                    singleValue: _props => React.null,
                    input: props => <Input props inputRef=containerRef />,
                    dropdownIndicator: _props => React.null,
                    indicatorSeparator: _props => React.null,
                  }
                  isDisabled=false
                  isLoading=false
                  isClearable=false
                  isRtl=false
                  isSearchable=true
                  filterOption
                  className={Some(className)}
                  classNamePrefix={Some(className)}
                  name="CountrySelect"
                  options=cs
                />
              </div>}
       </>;
     }}
  </div>;
};
