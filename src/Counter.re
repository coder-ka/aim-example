open Aim;
open Elements;

let increment = count => count + 1;

type actions =
  | Increment;

let createElement = (~children, ()) => {
  component(
    <>
      <div>
        <span> {text_(count => Js.Int.toString(count))} </span>
        <button onClick={(_, dispatch) => dispatch(Increment)}>
          {text("+")}
        </button>
      </div>
    </>,
    update => update(0),
    (action, update, count) => {
      switch (action) {
      | Increment => update(count + 1)
      }
    },
  );
};
