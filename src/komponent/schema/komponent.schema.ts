import { Prop, Schema, SchemaFactory } from '@nestjs/mongoose';
import { HydratedDocument } from 'mongoose';

export type Komponenter = HydratedDocument<Komponent>;

@Schema()
export class Komponent {
  @Prop({ unique: true, required: true })
  navn: string;

  @Prop({ required: true, default: 0 })
  antall: number;
}

export const KomponentSchema = SchemaFactory.createForClass(Komponent);
