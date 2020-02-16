open Aim;
open Elements;

let increment = count => count + 1;

type mutations =
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
    (update, mutation, count) => {
      switch (mutation) {
      | Increment => update(count + 1)
      }
    },
  );
};
