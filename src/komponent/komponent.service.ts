import { Injectable } from '@nestjs/common';
import { InjectModel } from '@nestjs/mongoose';
import { Model, Number } from 'mongoose';
import { CreateKomponentDto } from './dto/create-komponent.dto';
import { UpdateKomponentDto } from './dto/update-komponent.dto';
import { Komponent } from './schema/komponent.schema';

@Injectable()
export class KomponentService {
  constructor(
    @InjectModel(Komponent.name)
    private readonly komponentModel: Model<Komponent>,
  ) {}

  async create(createKomponentDto: CreateKomponentDto) {
    const nyKomponent = new this.komponentModel(createKomponentDto);
    return await nyKomponent.save();
  }

  async findAll() {
    return await this.komponentModel.find();
  }

  async findOne(id: string) {
    return await this.komponentModel.find({ navn: id });
  }

  async update(id: string, antallBestilt: number) {
    const komponent = await this.komponentModel.findOne({ navn: id });
    if (komponent) {
      if (komponent.antall >= antallBestilt) {
        komponent.antall -= antallBestilt;
        return await komponent.save();
      } else {
        return null;
      }
    }
  }
  remove(id: number) {
    return `This action removes a #${id} komponent`;
  }
}
