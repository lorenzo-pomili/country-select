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

module MenuList = {
  type menuListProps = {
    cx,
    clearValue,
    getStyles,
    getValue,
    hasValue: bool,
    isMulti: bool,
    isRtl: bool,
    options,
    selectOption,
    setValue,
    selectProps,
    theme,
    innerRef: React.ref(React.element),
    isLoading: bool,
    maxHeight: int,
    children: array(React.element),
  };

  [@bs.module "react-select"] [@bs.scope "components"] [@bs.val]
  external make: menuListProps => React.element = "MenuList";
};

module NoOptionsMessage = {
  [@bs.module "react-select"] [@bs.scope "components"] [@bs.val]
  external make: MenuList.menuListProps => React.element = "NoOptionsMessage";
};

type components = {
  [@bs.as "Option"]
  opt: Option.optionProps => React.element,
  [@bs.as "MenuList"]
  menuList: MenuList.menuListProps => React.element,
};

[@bs.module "react-select"] [@react.component]
external make:
  (
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
