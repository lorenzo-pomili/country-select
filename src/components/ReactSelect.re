type optionValue = Country.countryValue;

type opt = Country.t;

type cx;
type clearValue;
type getStyles;
type getValue = unit => option(array(opt));
type options = array(opt);
type selectOption;
type setValue;
type selectProps;
type theme;
type onBlur;
type onChange;
type onFocus;
type ariaAutocomplete;
type ariaLabel;
type ariaLabelledby;
type autoCapitalize;
type autoComplete;
type autoCorrect;
type id;
type spellCheck;
type tabIndex;
type value;

module Option = {
  type innerProps;

  type optionProps = {
    children: React.element,
    label: string,
    className: string,
    cx,
    getStyles,
    data: opt,
    isDisabled: bool,
    isFocused: bool,
    isSelected: bool,
    hasValue: bool,
    isMulti: bool,
    isRtl: bool,
    value: optionValue,
    innerRef: React.ref(React.element),
    innerProps,
    setValue,
    selectProps,
    theme,
    clearValue,
    getValue,
    options,
    selectOption,
    [@bs.as "type"]
    _type: string,
  };

  [@bs.module "react-select"] [@bs.scope "components"] [@bs.val]
  external make: optionProps => React.element = "Option";
};

module Control = {
  type controlProps;

  [@bs.module "react-select"] [@bs.scope "components"] [@bs.val]
  external make: controlProps => React.element = "Control";
};

type menuListProps;

module WindowedMenuList = {
  [@bs.module "react-windowed-select"] [@bs.val]
  external make: menuListProps => React.element = "WindowedMenuList";
};

module NoOptionsMessage = {
  [@bs.module "react-select"] [@bs.scope "components"] [@bs.val]
  external make: menuListProps => React.element = "NoOptionsMessage";
};

module Input = {
  type inputProps = {
    autoCapitalize,
    autoComplete,
    autoCorrect,
    cx,
    getStyles,
    id,
    innerRef: Js.Nullable.t(Dom.element) => unit,
    isDisabled: bool,
    isHidden: bool,
    onBlur,
    onChange,
    onFocus,
    selectProps,
    spellCheck,
    tabIndex,
    theme,
    [@bs.as "type"]
    _type: string,
    value,
    [@bs.as "aria-autocomplete"]
    ariaAutocomplete,
    [@bs.as "aria-label"]
    ariaLabel,
    [@bs.as "aria-labelledby"]
    ariaLabelledby,
  };

  [@bs.module "react-select"] [@bs.scope "components"] [@bs.val]
  external make: inputProps => React.element = "Input";
};

type singleValueProps;
type dropdownIndicatorProps;
type indicatorSeparatorProps;

type components = {
  [@bs.as "Option"]
  opt: Option.optionProps => React.element,
  [@bs.as "Input"]
  input: Input.inputProps => React.element,
  [@bs.as "SingleValue"]
  singleValue: singleValueProps => React.element,
  [@bs.as "MenuList"]
  menuList: menuListProps => React.element,
  [@bs.as "DropdownIndicator"]
  dropdownIndicator: dropdownIndicatorProps => React.element,
  [@bs.as "IndicatorSeparator"]
  indicatorSeparator: indicatorSeparatorProps => React.element,
};

type customStyles = {
  control: unit => Js.Dict.t(string),
  valueContainer: Js.Dict.t(string) => Js.Dict.t(string),
  option: (Js.Dict.t(int), Js.Dict.t(int)) => Js.Dict.t(int),
  menu: (Js.Dict.t(string), Js.Dict.t(string)) => Js.Dict.t(string),
};

[@bs.module "react-select"] [@react.component]
external make:
  (
    ~styles: option(customStyles),
    ~className: option(string),
    ~classNamePrefix: option(string),
    ~defaultValue: option(opt),
    ~value: option(opt),
    ~components: components,
    ~onChange: opt => unit,
    ~isDisabled: bool,
    ~isLoading: bool,
    ~menuIsOpen: option(bool),
    ~isClearable: bool,
    ~isRtl: bool,
    ~isSearchable: bool,
    ~name: string,
    ~filterOption: (opt, string) => bool,
    ~options: array(opt)
  ) =>
  React.element =
  "default";
