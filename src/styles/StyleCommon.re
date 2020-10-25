open Css;
let containerShadow =
  Shadow.box(
    ~inset=true,
    ~x=0->px,
    ~y=1->px,
    ~blur=3->px,
    ~spread=0->px,
    rgba(0, 0, 0, `num(0.1)),
  );

let ellipsis =
  style([
    overflowX(`hidden),
    textOverflow(`ellipsis),
    whiteSpace(`nowrap),
  ]);

let optionHeight = 26;
