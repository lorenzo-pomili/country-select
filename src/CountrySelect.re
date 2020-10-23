type state =
  | Loading
  | Error
  | Loaded(array(ReactSelect.opt));

let filterOption = (candidate: ReactSelect.opt, input) =>
  input !== ""
    ? Js.String.toLowerCase(input)
      ->Js.String.includes(Js.String.toLowerCase(candidate.label))
    : true;

let itemSize = 35;

let menuList = (props: ReactSelect.MenuList.menuListProps) => {
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

[@react.component]
let make = (~className, ~country, ~onChange) => {
  let (countries, setCountries) = React.useState(() => Loading);
  let (value, setValue) = React.useState(() => None);
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
       <ReactSelect
         defaultValue=None
         value
         onChange={v => {
           onChange(v);
           setValue(_p => Some(v));
         }}
         menuIsOpen=None
         components={
           opt: props =>
             ReactSelect.Option.make({
               ...props,
               children:
                 <CountryFlag countryCode={props.value}>
                   {props.children}
                 </CountryFlag>,
             }),
           menuList,
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
     }}
  </div>;
};

// {cs
//  ->Belt.Array.map(c =>
//      <div key={c.value}>
//        <CountryFlag countryCode={c.value} />
//        {c.label}->React.string
//      </div>
//    )-> React.array}
