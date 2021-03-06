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
      base->Js.Dict.set("height", 26);
      base->Js.Dict.set("padding", 0);
      base;
    },
    menu: (base, _state) => {
      base->Js.Dict.set("width", "230px");
      base->Js.Dict.set("borderBottomLeftRadius", "2px");
      base->Js.Dict.set("borderBottomRightRadius", "2px");
      base->Js.Dict.set("border", "solid 1px rgba(0, 0, 0, 0.08)");
      base->Js.Dict.set("boxShadow", "0 1px 3px 0 rgba(0, 0, 0, 0.1)");
      base->Js.Dict.set("backgroundColor", "#ffffff");
      base->Js.Dict.set("boxSizing", "contentBox");

      base->Js.Dict.set("marginTop", "1px");
      base->Js.Dict.set("left", "-1px");
      base->Js.Dict.set("marginBottom", "0px");
      base->Js.Dict.set("borderRadius", "0px");
      base;
    },
  });

[@bs.val] [@bs.scope "document"]
external documentAddEventListener: (string, ReactEvent.Mouse.t => unit) => unit =
  "addEventListener";
[@bs.val] [@bs.scope "document"]
external documentRemoveEventListener:
  (string, ReactEvent.Mouse.t => unit) => unit =
  "removeEventListener";

let setCloseOnClickOutside = (r: React.ref('a), close) => {
  React.useEffect1(
    () => {
      let handler = e => {
        let event = ReactEvent.Mouse.target(e);
        switch (r.current->Js.Nullable.toOption) {
        | None => ()
        | Some(c) =>
          ReactDOM.domElementToObj(c)##contains(event) ? () : close()
        };
      };

      documentAddEventListener("mousedown", handler);
      Some(() => documentRemoveEventListener("mousedown", handler));
    },
    [|r|],
  );
};

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
let make = (~className, ~country, ~onChange: Country.t => unit) => {
  let (countries, setCountries) = React.useState(() => Loading);
  let (value, setValue) = React.useState(() => None);
  let (isOpen, setIsOpen) = React.useState(() => false);
  let wholeElementRef = React.useRef(Js.Nullable.null);
  let containerRef = React.useRef(Js.Nullable.null);
  let activatorRef = React.useRef(Js.Nullable.null);

  let onChangeValue = v => {
    switch (v) {
    | None => ()
    | Some(v1) => onChange(v1)
    };
    setValue(_p => v);
  };

  let toggleOpen = () => setIsOpen(prev => !prev);

  React.useEffect1(
    () => {
      if (isOpen) {
        Utils.focusRef(containerRef);
      };
      None;
    },
    [|value|],
  );

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
          onChangeValue(cs->Belt.Array.getBy(c => c.value === cVal))
        };
        setCountries(_prev => Loaded(cs));
      },
    );

    Some(() => {GetData.abort(request)});
  });

  setCloseOnClickOutside(wholeElementRef, () => setIsOpen(_prev => false));

  <div ref={ReactDOM.Ref.domRef(wholeElementRef)}>
    {switch (countries) {
     | Loading => <div> "Loading..."->React.string </div>
     | Error => <div> "Error"->React.string </div>
     | Loaded(cs) =>
       let text =
         switch (value) {
         | None => ""
         | Some(v) => v.label
         };
       <div
         onKeyDown={e => {
           let key = e->ReactEvent.Keyboard.key;
           switch (key) {
           | "ArrowDown" when !isOpen => toggleOpen()
           | "Escape" when isOpen =>
             toggleOpen();
             Utils.focusRef(activatorRef);
           | "Delete" => onChangeValue(Some({value: "", label: ""}))
           | _ => ()
           };
         }}>
         <Activator text onClick={_e => toggleOpen()} activatorRef />
         {!isOpen
            ? React.null
            : <div className=Style.container>
                <ReactSelect
                  styles=selectComponentsCustomStyle
                  defaultValue=None
                  value
                  onChange={v => onChangeValue(Some(v))}
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
                    menuList: props =>
                      ReactSelect.WindowedMenuList.make(props),
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
       </div>;
     }}
  </div>;
};
