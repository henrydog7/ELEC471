# ELEC 471 – Brake-Light Controller (Simulink: Lab 2 + Lab 3)

This repo holds the Simulink work for Lab 2 (activity) and Lab 3 (Verified Design).
Everything you need for the Cadmus write-up is summarized below.

---

## Files

| File | What it is |
|---|---|
| `Lab3_BreakLight.slx` | **Lab 3 model**: final design, Requirements Table, MCDC settings |
| `Lab2_Start_2025b.slx` | Lab 2 activity model (brake + acceleration version) |
| `vehicle_data.m` | Prof's vehicle data (unchanged). **Run this before opening the model.** |
| `*.png` | Block icons (unchanged from the prof's zip) |
| MC/DC coverage report (PDF) | Coverage report for the "Verification Plan and Results" chapter |

**Opening the model:** in MATLAB, set the Current Folder to this repo, run `vehicle_data.m`, then double-click the `.slx` in the Files panel.
Saved in **R2025b**. R2026a can open it, but if you save it in R2026a, export it back with *Save → Export Model to → Previous Version → R2025b* so everyone can still open it.

---

## Lab 3: Design Model (for the "Design Model" chapter)

The logic is in the subsystem **`Brake_Light_Logic`**. It has three inputs (Brake, One_Pedal, Throttle) and one output (lamp).

```
lamp = (Brake > 0) OR (One_Pedal == 1 AND Throttle < 30)
```

Blocks inside `Brake_Light_Logic`:
- `Compare To Constant (> 0)` on Brake → TSR1a
- `Compare To Constant (== 1)` on One_Pedal and `Compare To Constant (< 30)` on Throttle → `AND` → TSR1b
- `OR` of both paths → lamp. When neither condition holds the output is false, so the lamp is OFF by default (TSR7).

Signals come from the existing vehicle model through From blocks (`[Brake]`, `[One_Pedal]`, `[Throttle]`).
The lamp output also feeds the Requirements Table, which checks it.

**Screenshots to take for Cadmus:** (1) the top-level view showing the From blocks, `Brake_Light_Logic`, `lamp` and the Requirements Table; (2) the inside of `Brake_Light_Logic`; (3) the Requirements Table (both tabs).

---

## Lab 3: Requirements Table (formalized TSRs)

**Requirements tab** (postconditions, no actions or durations):

| # | TSR | Precondition | Postcondition |
|---|---|---|---|
| 1 | TSR1a: lamp ON when brake pressed | `brake_pedal > 0` | `lamp == true` |
| 2 | TSR1b: lamp ON in one-pedal slowing | `one_pedal == 1 && throttle < 30` | `lamp == true` |
| 3 | TSR7: lamp OFF otherwise (default) | `brake_pedal <= 0 && ~(one_pedal == 1 && throttle < 30)` | `lamp == false` |

**Assumptions tab** (input ranges from the CAN data dictionary):

| # | Assumption | Postcondition |
|---|---|---|
| 1 | Brake pedal is 0–100 % | `brake_pedal >= 0 && brake_pedal <= 100` |
| 2 | Throttle is 0–100 % | `throttle >= 0 && throttle <= 100` |
| 3 | One_Pedal is boolean | `one_pedal == 0 \|\| one_pedal == 1` |

The table also has an `acceleration` input that no row uses (left over from Lab 2). It only causes a harmless "not used" warning.

---

## Lab 3: Formalization Report (for "Verification Plan and Results")

**Formalized:** TSR1a, TSR1b, TSR7.

**Partly formalized:** TSR1a and TSR1b say "within 50 ms". The timing isn't formalized because the logic is combinational and responds in the same time step, so the 50 ms bound is met trivially in the model.

**Not formalized, and why** (the model only has vehicle signals: Brake, Throttle, One_Pedal, gear, speed/acceleration; it has no CAN frames, lamp current, watchdog, hazard signal or display):

| TSR | Reason not formalized |
|---|---|
| TSR2a, TSR2b | Need raw CAN 0x512 frames (message length, receive timing). The model gets already-decoded signals, not CAN messages. |
| TSR3 | Out-of-range checks on CAN 0x512 signals over 3 consecutive messages. There's no message stream in the model, and the inputs are already range-limited (see Assumptions). |
| TSR4, TSR8 | Need brake-light **current** feedback. There's no lamp current signal in the model. |
| TSR5 | Watchdog timeout / reboot is a runtime/hardware behaviour and isn't represented in Simulink. |
| TSR6, TSR10 | Driver_Display messages and their priority queue. There's no display output in the model. |
| TSR9 | Needs Hazard_Signal and cycling detection. There's no hazard input in the model. |
| TSR11 | Memory/buffer implementation detail (QM), not a behaviour that can be checked at model level. |
| TSR12 | Independent re-check of the command needs a redundant channel and an alarm/safe-state output, which the model doesn't have. (The Requirements Table itself acts as an independent check of the lamp command in verification.) |

---

## Lab 3: Verification Results

- **Analyze Table:** no inconsistency issues and no incompleteness issues.
- **Property Proving (Design Verifier):** all 3 requirements **Valid**. One objective was falsified: `Transmission/Proof Objective`. That's a block in the prof's Transmission subsystem (gear range), not part of our logic.
- **Test Generation (Model coverage objectives = MCDC):** 130/130 objectives satisfied, 0 unsatisfiable.
- **Coverage report** ("Simulate tests and produce a model coverage report"): **`Brake_Light_Logic` = 100 % MC/DC.** See the PDF report in this repo.

---

## Lab 2 Activity (for reference)

- Requirements used brake + acceleration (as the Lab 2 handout instructed):
  1. `brake_pedal > 0` → `lamp == true`
  2. `acceleration < -1` → `lamp == true`
  3. `brake_pedal <= 0 && acceleration >= -1` → `lamp == false`
- Logic: `lamp = (Brake > 0) OR (Acceleration < -1)`
- Analyze Table: no issues. Prove Properties: 3 requirements valid (same Transmission/Proof Objective falsified, prof's block).
- Tests exported to Simulink Test: **3/3 passed.**
- For Lab 3 the acceleration rule was replaced by TSR1b (One_Pedal + Throttle), because our TSRs don't contain an acceleration requirement.

---

## Open items for Cadmus (feedback from Lab 2)

These are wording fixes in the TSR table. They don't affect the Simulink model.
1. **TSR2a timing:** 3 messages × 20 ms = 60 ms, which is more than the 50 ms in the FSR. Make the numbers consistent.
2. **TSR1 atomicity:** remove the part describing how speed is calculated. TSRs should say *what*, not *how*.
