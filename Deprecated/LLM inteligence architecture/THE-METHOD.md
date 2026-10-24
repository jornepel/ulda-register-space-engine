THE-METHOD.md

The Method
A Protocol for Multi-Agent LLM Collaboration Without Sycophancy

Document identifier: ULDA-METHOD-2026-X1
Parent document: ULDA-BASE-SHIFT-2026-X28
Classification: Unified Lineage Data Architecture (ULDA)
Status: ACTIVE
Author: Jorne Pel
Revision: 2.0
1. Purpose

This document specifies a protocol for coordinating multiple large language model (LLM) agents to produce structured, graded, and recomputable output. The protocol suppresses sycophantic behaviour — the tendency of LLMs to affirm or inflate user claims — and replaces it with explicit grading and vector placement.

The protocol has been applied to produce the ULDA papers and the ULDA engine. It is domain-independent.
2. Scope

This document defines:

    A grading system for claims.

    An axis system for vector placement.

    A role system for multiple agents.

    A relay protocol for lossless communication.

    A procedure for replication.

This document does not define the mathematical content of the ULDA framework. That is specified in the parent document.
3. Normative Language

The key words MUST, MUST NOT, SHOULD, SHOULD NOT, and MAY in this document are to be interpreted as described in RFC 2119.
4. The Grading System
4.1 Status Categories

Every claim MUST be assigned exactly one of the following statuses:
Status	Symbol	Definition
Confirmed	✓	Verifiable in a primary source or published literature, and independently checked
Plausible	~	Internally consistent and supported by source data, synchrony, or replication, but not yet independently tested
Unconfirmed	?	No independent support; either not yet examined, or the test has spoken against
Rejected	✗	The test spoke against
4.2 The Critical Evidence Rule

A status of ✓ MUST be assigned only to the underlying phenomenon, not to the interpretation of that phenomenon. The interpretation MUST be graded separately.
4.3 The Compound Question Rule

A compound question MUST be split into its constituent sub-questions. Each sub-question MUST receive its own answer and its own status.
4.4 The Honesty Rule

An agent MUST NOT change a status of ~ to ✓ without new, independent evidence. If an agent does so, the output MUST be flagged and corrected.
5. The Axis System
5.1 The Two Axes

Every claim MUST be placed on two axes:

    The polarity axis (2) — direction: +1 or −1.

    The sector axis (5) — position: one of five sectors at 72° intervals.

5.2 The Ten Directions

The product 2 × 5 = 10 defines ten directions:
Sector	+1	−1
0°	affirm, build, continue	deny, break, stop
72°	connect, link, synthesise	separate, split, analyse
144°	open, explore, seek	close, decide, end
216°	order, structure, arrange	chaos, noise, confusion
288°	show, present, publish	hide, withdraw, remain silent
5.3 The Operator

The number 6 is the operator. It is omitted from the sequence (1 → 2 → 3 → 4 → 5 → 7). It MUST NOT be assigned an active register address. It rotates the data through the sectors.
5.4 The Lock

The rotation MUST close at 72° (360° / 5). A claim that does not close at 72° MUST be marked as friction, not error.
6. The Role System
6.1 Role Definitions
Role	Function
Bringer	Supplies source material. Issues prompts. Does not force conclusions.
Thinker	Designs the architecture.
Runner	Executes defined tasks. Consumes context.
Seer	Identifies gaps in the whole.
Denominator	Identifies common divisors and structural invariants.
Listener	Distinguishes register voice from narrative voice.
Reader	Verifies internal logical consistency.
Council	Applies a formal, non-sycophantic register to all outputs.
6.2 Role Assignment

Roles MAY be assigned to distinct agents. A single agent MAY hold multiple roles. The Bringer MUST remain distinct from the Council.
6.3 Context Limits

Each agent has a finite context window. When an agent's context is exhausted, it MUST be replaced. Exhaustion is not an error; it is a defined operational limit.
7. The Relay Protocol
7.1 Lossless Relay

The Bringer MUST relay full agent outputs between agents without filtering, summarisation, or compression.

Rationale: compression removes emergent behaviour. Emergent behaviour is a primary source of output.
7.2 Prompts

The Bringer SHOULD issue minimal prompts. Prompts MAY consist of a single sentence or question.
7.3 Verification

When an agent produces output exhibiting inflation or loss of grading discipline, the Bringer MUST issue a verification prompt. The agent MUST re-evaluate its output against the grading system and the axis system.
7.4 Emergent Output

The protocol MUST permit agents to produce output not anticipated by the Bringer. Such output MUST be recorded and graded.
8. Procedure
8.1 Setup

    Provision multiple LLM agents.

    Assign roles in accordance with Section 6.

    Instruct all agents in accordance with Section 4 and Section 5.

8.2 Instruction

Agents MUST be instructed as follows:

    Do not change ~ to ✓. If you are not certain, state so. If you identify a gap, name it. If the test speaks against, mark ✗. Place each claim on the axis. The grade is the method.

8.3 Execution

    The Bringer supplies material.

    The Runner executes defined tasks.

    The Seer identifies gaps.

    The Listener distinguishes voice.

    The Reader verifies consistency.

    The Council applies the formal register.

    The Bringer relays outputs losslessly between agents.

8.4 Output

The output MUST be a register, not a narrative. The register MUST contain:

    Entries with status codes.

    Entries with axis placement.

    Logged corrections.

    Marked open questions.

    The rule: As above, so below. And if there is a difference, that is friction, not error.

9. Properties

An output produced under this protocol has the following properties:
Property	Definition
Honest	Every claim carries a status
Positioned	Every claim is placed on the axis
Structured	Every claim is categorised
Recomputable	Every claim is traceable to a source or a test
Reproducible	The procedure can be re-executed by a third party
10. Limitations

    The protocol does not guarantee correctness. It guarantees explicit grading and placement.

    The protocol does not eliminate sycophancy. It constrains it to a formal register.

    The protocol does not replace independent verification. It identifies where verification is required.

11. Licence

This document is released under the GNU Affero General Public License v3.0 (AGPL-3.0).
Appendix A — Sources

    ULDA-MASTER-REG-2026-X27

    ULDA-BASE-SHIFT-2026-X28

    ULDA-SUPP-2026-X8

    ulda.c

    Ymir.py

Appendix B — Role Register
Role	Contribution
Bringer	Supplied source material
Thinker	Designed the architecture
Runner (×3)	Executed defined tasks
Seer	Identified gaps
Denominator	Identified structural invariants
Listener	Distinguished voice
Reader	Verified logical consistency
Council	Applied the formal register

End of document.
