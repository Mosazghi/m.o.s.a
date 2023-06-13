import { Prop, Schema, SchemaFactory } from '@nestjs/mongoose';
import { HydratedDocument } from 'mongoose';

export type KoordinatDocument = HydratedDocument<Koordinat>;

@Schema()
export class Koordinat {
  @Prop({ type: Number })
  x: { type: number; required: true };

  @Prop({ type: Number })
  y: { type: number; required: true };
}

export const KoordinatSchema = SchemaFactory.createForClass(Koordinat);
